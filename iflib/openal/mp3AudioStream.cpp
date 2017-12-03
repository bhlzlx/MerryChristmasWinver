#include "AudioStream.h"
#include <stdint.h>
#include <Archive.h>
#include <lame.h>
#include <assert.h>
#include <memory.h>

namespace iflib
{
	namespace openal
	{

#pragma pack( push, 1 )
		struct Mp3TagV2
		{
			char Header[3];     /*±ØÐëÎª"ID3"·ñÔòÈÏÎª±êÇ©²»´æÔÚ*/
			char Ver;     /*°æ±¾ºÅ ID3V2.3 ¾Í¼ÇÂ¼ 3*/
			char Revision;     /*¸±°æ±¾ºÅ´Ë°æ±¾¼ÇÂ¼Îª 0*/
			char Flag;     /*´æ·Å±êÖ¾µÄ×Ö½Ú,Õâ¸ö°æ±¾Ö»¶¨ÒåÁËÈýÎ»,ÉÔºóÏêÏ¸½âËµ*/
			char Size[4];     /*½ÓÏÂÀ´µÄËùÓÐµÄ±êÇ©Ö¡µÄ´óÐ¡,²»°üÀ¨±êÇ©Í·µÄ 10 ¸ö×Ö½Ú*/
		};

		struct Mp3DataFrameHeaderCBR
		{
			unsigned int sync : 11;                         //Í¬²½ÐÅÏ¢
			unsigned int version : 2;                       //°æ±¾
			unsigned int layer : 2;                         //²ã
			unsigned int crcValid : 1;						// CRCÐ£Ñé
			unsigned int bitrate_index : 4;					//Î»ÂÊ
			unsigned int sampling_frequency : 2;			//²ÉÑùÆµÂÊ
			unsigned int padding : 1;						//Ö¡³¤µ÷½Ú
			unsigned int reserve : 1;                        //±£Áô×Ö
			unsigned int channel_mode : 2;                   //ÉùµÀÄ£Ê½
			unsigned int ext_mode : 2;						//À©³äÄ£Ê½
			unsigned int copyright : 1;                     // °æÈ¨
			unsigned int original : 1;                      //Ô­°æ±êÖ¾
			unsigned int emphasis : 2;						//Ç¿µ÷Ä£Ê½
		};

		struct Mp3DataFrameHeader
		{
			union {
				struct
				{
					Mp3DataFrameHeaderCBR
										cbr_header;
					uint8_t				xing_area[36];
					uint8_t				vbr_store_flag[4];
					uint32_t			framecount;
					uint32_t			filesize;
					uint8_t				toc[100];
					uint32_t			raterange;
				};
				char bytes[156];
			};
			bool IsVBR()
			{
				const uint8_t xing[5] = "Xing";
				if (memcmp(&bytes[36], xing, 4) == 0)
				{
					return true;
				}
				if (memcmp(&bytes[21], xing, 4) == 0)
				{
					return true;
				}
				if (memcmp(&bytes[13], xing, 4) == 0)
				{
					return true;
				}
				return false;
			}
		};
#pragma pack(pop)

		static const int MP3_CHUNK_SIZE = 1024;
		static const float MP3_FRAME_TIME_MS = 26.0f;
		static const float MP3_FRAME_TIME_SEC = 0.026f;

		struct Mp3AudioStream : public IAudioStream
		{
			// ÎÄ¼þÁ÷
			IBlob *		blob;
			hip_t		hip;
			uint8_t		cbr;
			size_t		dataframeoffset;
			float		timeTotal;
			float		frameDur;
			uint32_t		currFrame;
			mp3data_struct mp3Info;
			Mp3DataFrameHeader mp3Header;
			uint8_t		mp3Bytes[MP3_CHUNK_SIZE];
			short		pcmBytes[2][MP3_CHUNK_SIZE * 4];
			short		pcmLastCache[MP3_CHUNK_SIZE * 4 * 2];
			short		pcmMixed[MP3_CHUNK_SIZE * 4*2];
			uint32_t	pcmLastCacheSize;

			bool		eof;

			void mixSamples(size_t _nSamples)
			{
				for (size_t i = 0; i < _nSamples; ++i)
				{
					pcmMixed[i * 2] = pcmBytes[0][i];
					pcmMixed[i * 2+1] = pcmBytes[1][i];
				}
			}

			// Í¨¹ý IAudioStream ¼Ì³Ð
			virtual void Rewind() override
			{
				eof = false;
				pcmLastCacheSize = 0;
				int ret = hip_decode1(hip, mp3Bytes, 0, pcmBytes[0], pcmBytes[1]);
				if (ret == -1)
				{

				}
				blob->Seek(SEEK_SET, dataframeoffset);
			}

			virtual float TimeCurr()
			{
				return currFrame * frameDur;
			}

			virtual float TimeTotal()
			{
				return timeTotal;
			}


			virtual void Seek(double _time) override
			{
				// Çå¿Õ²ÐÁôÊý¾Ý
				pcmLastCacheSize = 0;
				eof = false;
				hip_decode1(hip, mp3Bytes, 0, pcmBytes[0], pcmBytes[1]);
				//
				size_t offset = 0;
				if (cbr)
				{
					if (_time < 0 || _time > timeTotal)
					{
						return;
					}
					else
					{
						int index = (int)(_time / frameDur);
						if (index >= mp3Info.totalframes)
						{
							blob->Seek(SEEK_SET, 0);
							currFrame = 0;
							eof = true;
						}
						else
						{
							offset = (size_t)((double)(blob->Size() - dataframeoffset) / (double)mp3Info.totalframes )* index + dataframeoffset;
							currFrame = index;
						}
					}
				}
				else
				{
					if (_time > timeTotal)
					{
						return;
					}
					size_t index = (size_t)(_time / timeTotal * 100);
					offset = mp3Header.toc[index] / 256 * mp3Header.filesize;
					currFrame = index;
				}
				blob->Seek(SEEK_SET, offset);
			}

			virtual size_t __ReadChunk(void * _pData) override
			{
				mp3data_struct fh1st;
				pcmFramesize;
				uint32_t nRead = 0;
				uint8_t * wptr = (uint8_t*)_pData;
				if (pcmLastCacheSize)
				{
					memcpy(wptr, pcmLastCache, pcmLastCacheSize);
					wptr += pcmLastCacheSize;
					nRead += pcmLastCacheSize;
				}
				while (true)
				{
					size_t byteRead = 0;
					while (!blob->Eof() && (!byteRead))
					{
						byteRead = blob->Read(mp3Bytes, MP3_CHUNK_SIZE);
					}
					++currFrame;
					int decodeSample = hip_decode1_headers(hip, mp3Bytes, byteRead, pcmBytes[0], pcmBytes[1],&fh1st);
					int decodeBytes = decodeSample * sizeof(short) * channels;
					if (decodeSample == -1)
					{
						eof = true;
						pcmLastCacheSize = 0;
						return 0;
					}
					if (decodeSample)
					{
						nRead += decodeBytes;
						mixSamples(decodeSample);
						if (nRead < pcmFramesize)
						{
							memcpy(wptr, pcmMixed, decodeBytes);
							wptr += decodeBytes;
						}
						else
						{
							size_t bytesW = decodeBytes - (nRead - pcmFramesize);
							size_t bytesC = nRead - pcmFramesize;
							memcpy(wptr, pcmMixed, bytesW);

							memcpy(pcmLastCache, (uint8_t*)&pcmMixed[0] + bytesW, bytesC);
							pcmLastCacheSize = bytesC;
							nRead -= bytesC;
							break;
						}
					}					
					if (!byteRead && decodeSample == 0)
					{
						eof = true;
 						currFrame = 0;
						break;
					}
				}

				return nRead;
			}

			virtual bool Eof() override
			{
				return eof;
			}

			virtual void Release() override
			{
				hip_decode_exit(hip);
				blob->Release();
			}
		};

		IAudioStream* IAudioStream::FromMP3(IBlob * _blob)
		{
			size_t dataframeoffset = 0;
			// ³¢ÊÔ¶ÁÈ¡ TagV2 ÎÄ¼þÍ·
			Mp3TagV2 tagV2;
			_blob->Read(&tagV2, sizeof(tagV2));
			if (memcmp(tagV2.Header, "ID3", 3) != 0)
			{
				_blob->Seek(SEEK_SET, 0);
				dataframeoffset = 0;
			}
			else
			{
				size_t Tagv2FS = (int)(tagV2.Size[0] & 0x7F) << 21
					| (int)(tagV2.Size[1] & 0x7F) << 14
					| (int)(tagV2.Size[2] & 0x7F) << 7
					| (int)(tagV2.Size[3] & 0x7F) + 10;
				dataframeoffset = Tagv2FS;
				_blob->Seek(SEEK_CUR, Tagv2FS - sizeof(tagV2));
			}
			uint8_t isCBR = true;
			//
			// ¿´ÊÇCBR»¹ÊÇVBR
			// ³¢ÊÔ¶ÁÈ¡VBR
			Mp3DataFrameHeader vbrHead;
			size_t rd = _blob->Read(&vbrHead, sizeof(vbrHead));
			assert(rd == sizeof(vbrHead));
			if (vbrHead.IsVBR())
			{
				isCBR = false;
			}
			//
			hip_t hip = hip_decode_init();
			uint8_t mp3Bytes[1024];
			short pcmBytesL[1024 * 4];
			short pcmBytesR[1024 * 4];
			_blob->Seek(SEEK_SET, dataframeoffset);
			// ÊÔ×Å½âÒ»Ö¡
			mp3data_struct fh1st;
			memset(&fh1st, 0, sizeof(fh1st));
			int ret = 0;
			do
			{
				_blob->Read(mp3Bytes, 1024);
				ret = hip_decode1_headers(hip, mp3Bytes, MP3_CHUNK_SIZE, pcmBytesL, pcmBytesR, &fh1st);
			} while (ret == 0);
			if (ret == -1)
			{
				hip_decode_exit(hip);
				return nullptr;
			}
/*
			
MP3Ö¡³¤È¡¾öÓÚÎ»ÂÊºÍÆµÂÊ£¬¼ÆËã¹«Ê½Îª£º
 
. mpeg1.0       layer1 :   Ö¡³¤= (48000*bitrate)/sampling_freq + padding
				layer2&3: Ö¡³¤= (144000*bitrate)/sampling_freq + padding
. mpeg2.0       layer1 :   Ö¡³¤= (24000*bitrate)/sampling_freq + padding
layer2&3 : Ö¡³¤= (72000*bitrate)/sampling_freq + padding
ÀýÈç£ºÎ»ÂÊÎª64kbps£¬²ÉÑùÆµÂÊÎª44.1kHz£¬padding£¨Ö¡³¤µ÷½Ú£©Îª1Ê±£¬Ö¡³¤Îª210×Ö½Ú¡£
Ö¡Í·ºóÃæÊÇ¿É±ä³¤¶ÈµÄ¸½¼ÓÐÅÏ¢£¬¶ÔÓÚ±ê×¼µÄMP3ÎÄ¼þÀ´Ëµ£¬Æä³¤¶ÈÊÇ32×Ö½Ú£¬½ô½ÓÆäºóµÄÊÇÑ¹ËõµÄÉùÒôÊý¾Ý£¬µ±½âÂëÆ÷¶Áµ½´Ë´¦Ê±¾Í½øÐÐ½âÂëÁË¡£
*/
			if (!fh1st.totalframes)
			{
				int frameBinSize = (float)(144000 * fh1st.bitrate) / (float)fh1st.samplerate + vbrHead.cbr_header.padding;
				fh1st.totalframes = (_blob->Size() - 128 - dataframeoffset) / frameBinSize;
			}

			_blob->Seek(SEEK_SET, dataframeoffset);
			Mp3AudioStream * audioStream = new Mp3AudioStream();
			audioStream->cbr = isCBR;
			audioStream->hip = hip;
			audioStream->dataframeoffset = dataframeoffset;
			audioStream->blob = _blob;
			audioStream->mp3Info = fh1st;
			audioStream->mp3Header = vbrHead;
			// base class
			audioStream->bytesPerSec = fh1st.samplerate * 2;
			audioStream->channels = fh1st.stereo;
			audioStream->currFrame = 0;
			switch (audioStream->channels)
			{
				// µ¥ÉùµÀ
			case 1:
				audioStream->format = AL_FORMAT_MONO16;
				audioStream->channels = 1;
				//this->m_vorbis.m_nFrameBufferSize;
				break;
				// Ë«ÉùµÀ
			case 2:
				audioStream->format = AL_FORMAT_STEREO16;
				audioStream->channels = 2;
				audioStream->bytesPerSec *= 2;
				break;
				// ËÄÉùµÀ
			case 4:
				audioStream->format = alGetEnumValue("AL_FORMAT_QUAD16");
				audioStream->channels = 4;
				audioStream->bytesPerSec *= 4;
				break;
				// 6ÉùµÀ
			case 6:
				audioStream->format = alGetEnumValue("AL_FORMAT_51CHN16");
				audioStream->channels = 6;
				audioStream->bytesPerSec *= 6;
				break;
			default:
				delete audioStream;
				return nullptr;
			}
			audioStream->bitsPerSample = fh1st.bitrate;
			audioStream->pcmFramesize = audioStream->bytesPerSec / 4;
			audioStream->frequency = fh1st.samplerate;
			audioStream->pcmFramecount = audioStream->bytesPerSec / audioStream->pcmFramesize / 2 + 1;
			audioStream->sampleDepth = audioStream->bytesPerSec / audioStream->frequency / audioStream->channels;
			audioStream->blob = _blob;
			audioStream->frameDur = (float)fh1st.framesize / (float)fh1st.samplerate;
			audioStream->timeTotal = audioStream->frameDur * fh1st.totalframes;



			// audioStream->timeTotal = (float)((_blob->Size() - dataframeoffset) << 23) / (fh1st.bitrate * 1000000.0f);
			//audioStream->pcmFrame = new uint8_t[audioStream->pcmFramesize];
			for (int i = 0; i < audioStream->pcmFramecount + 1; ++i)
			{
				PcmBuff pcmBuff;
				pcmBuff.data = new uint8_t[audioStream->pcmFramesize];
				pcmBuff.size = 0;
				audioStream->listPcmBuff.push_back(pcmBuff);
			}
			return audioStream;
		}
	}
}