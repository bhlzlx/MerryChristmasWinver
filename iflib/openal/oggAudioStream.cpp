#include "AudioStream.h"
#include <stdint.h>
#include <Archive.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>
#include <assert.h>

namespace iflib
{
	namespace openal
	{
		size_t vorbisRead(void * _pData, size_t _nElement, size_t _nCount, void * _pFile)
		{
			IBlob* blob = (IBlob*)_pFile;
			return blob->Read(_pData, _nCount * _nElement);
		}

		int vorbisSeek(void * _pFile, ogg_int64_t _nOffset, int _flag)
		{
			IBlob* blob = (IBlob*)_pFile;
			return blob->Seek(_flag, (uint32_t)_nOffset);
		}

		int vorbisClose(void * _pFile)
		{
			IBlob* blob = (IBlob*)_pFile;
			blob->Release();
			return 1;
		}

		long vorbisTell(void * _pFile)
		{
			IBlob* blob = (IBlob*)_pFile;
			return blob->Tell();
		}

		static ov_callbacks IflibVorbisCallback = {
			(size_t(*)(void *, size_t, size_t, void *))  vorbisRead,
			(int(*)(void *, ogg_int64_t, int))           vorbisSeek,
			(int(*)(void *))                             vorbisClose,
			(long(*)(void *))                            vorbisTell
		};

		struct OggAudioStream : public IAudioStream
		{
			// ÎÄ¼þÁ÷
			IBlob * blob;
			// vorbis ÎÄ¼þ¾ä±ú
			OggVorbis_File		oggvorbisFile;
			// vorbisÐÅÏ¢
			vorbis_info*		vorbisInfo;
			// vorbis½Å×¢
			vorbis_comment*		vorbisComment;
			//
			bool eof;
			// Í¨¹ý IAudioStream ¼Ì³Ð
			OggAudioStream()
			{
				eof = false;
				vorbisInfo = nullptr;
				vorbisComment = nullptr;
			}

			virtual void Rewind() override
			{
				ov_time_seek(&oggvorbisFile, 0);
				eof = false;
			}

			virtual void Seek(double _time) override
			{
				ov_time_seek(&oggvorbisFile, _time);
				eof = false;
			}

			virtual float TimeCurr()
			{
				return ov_time_tell(&oggvorbisFile);
			}

			virtual float TimeTotal()
			{
				return ov_time_total(&oggvorbisFile, -1);
			}

			virtual size_t __ReadChunk(void * _pData) override
			{
				int size = 0;
				int result;
				int section;
				while (size < pcmFramesize)
				{
					result = ov_read(
						&this->oggvorbisFile,
						(char*)_pData + size,
						pcmFramesize - size,
						0,
						2,
						1,
						&section
					);
					// ÎÄ¼þÎ²
					if (result == 0)
					{
						eof = true;
						break;
					}
					// Õý³£¶ÁÈ¡
					else if (result > 0)
					{
						size = result + size;
					}
					// ·¢Éú´íÎó
					else
					{
						assert(result != OV_HOLE && result != OV_EBADLINK && result != OV_EINVAL);
						break;
					}
				}
				return size;
			}

			virtual bool Eof() override
			{
				return eof;
			}

			virtual void Release() override
			{
				ov_clear(&oggvorbisFile);
				delete this;
			}
		};

		IAudioStream* IAudioStream::FromOGG(IBlob * _blob)
		{
			OggVorbis_File oggvorbisFile;
			int32_t error = ov_open_callbacks(_blob, &oggvorbisFile, NULL, 0, IflibVorbisCallback);
			if (error != 0)
			{
				return nullptr;
			}
			// ´´½¨OggAudioStream¶ÔÏó
			OggAudioStream * audioStream = new OggAudioStream();
			audioStream->blob = _blob;
			audioStream->oggvorbisFile = oggvorbisFile;
			audioStream->vorbisInfo = ov_info(&audioStream->oggvorbisFile, -1);
			audioStream->vorbisComment = ov_comment(&audioStream->oggvorbisFile, -1);
			/******************************************************
			ÕâÀï½âÊÍÒ»ÏÂ´úÂë
			PCMÊý¾Ý´óÐ¡¼ÆËã Ã¿Ãë´óÐ¡ = ²ÉÑùÂÊ * Î»¿í / 8 * ÉùµÀÊý
			Î»¿íÊÇ16,ÉùµÀÊýÊÇ1¼´
			rate * 16 / 8 * 1
			¼´ rate * 2 ÕâÊÇÒ»ÃëµÄ´óÐ¡
			250ms¶ÔÓ¦µÄ´óÐ¡Ó¦¸ÃÊÇrate / 2
			ËùÒÔÕâÀï¾ÍÊÇrate >> 1,Î»²Ù×÷ÓÒÒÆÒ»Î»¼´¿ÉÊµÏÖ³ý2
			µ«ÊÇ×îºó»¹ÓÐ¸öblock¶ÔÆë,ÕâÀïÒòÎªÊÇµ¥ÉùµÀ,16Î»,Á½¸ö×Ö½ÚµÄ¶ÔÆë
			******************************************************/
			audioStream->bytesPerSec = audioStream->vorbisInfo->rate * 2;
			switch (audioStream->vorbisInfo->channels)
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
				ov_clear(&audioStream->oggvorbisFile);
				delete audioStream;
				return nullptr;
			}
			audioStream->pcmFramesize = audioStream->bytesPerSec / 4;
			audioStream->pcmFramecount = audioStream->bytesPerSec / audioStream->pcmFramesize;
			audioStream->bitsPerSample = audioStream->vorbisInfo->bitrate_nominal;
			audioStream->frequency = audioStream->vorbisInfo->rate;
			audioStream->sampleDepth = audioStream->bytesPerSec / audioStream->frequency / audioStream->channels;
			//
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