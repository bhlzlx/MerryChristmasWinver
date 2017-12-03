#include "AudioStream.h"
#include <stdint.h>
#include <Archive.h>
#include <memory.h>

namespace iflib
{
	namespace openal
	{
		static const float FRAME_BUFFER_TIME_MS = 500.0f;

		struct RIFF_HEADER
		{
			uint8_t		szRiffID[4];  // 'R','I','F','F'
			uint32_t	dwRiffSize;
			uint8_t		szRiffFormat[4]; // 'W','A','V','E'
		};

		struct WAVE_FORMAT
		{
			int16_t wFormatTag;
			int16_t wChannels;
			int32_t dwSamplesPerSec;
			int32_t dwAvgBytesPerSec;
			int16_t wBlockAlign;
			int16_t wBitsPerSample;
		};

		struct FMT_BLOCK
		{
			uint8_t		szFmtID[4]; // 'f','m','t',' '
			uint32_t	dwFmtSize;
			WAVE_FORMAT wavFormat;
		};

		struct CHUNK_INFO
		{
			uint8_t  szChunkID[4];
			int32_t  dwChunkSize;
		};

		struct DATA_CHUNK
		{
			ALsizei					nDataSize;
			ALchar*					pData;
		};

		struct WAVE_INFO
		{
			DATA_CHUNK	m_DataChunk;
			int32_t		m_format;
			int32_t		m_samplePerSec;
		};

		int WAVEFormat2AL(FMT_BLOCK * pFMT)
		{
			ALenum result = 0;
			if (pFMT->wavFormat.wChannels == 1)
			{
				switch (pFMT->wavFormat.wBitsPerSample)
				{
				case 4:
					result = alGetEnumValue("AL_FORMAT_MONO_IMA4");
					break;
				case 8:
					result = alGetEnumValue("AL_FORMAT_MONO8");
					break;
				case 16:
					result = alGetEnumValue("AL_FORMAT_MONO16");
					break;
				}
			}
			else if (pFMT->wavFormat.wChannels == 2)
			{
				switch (pFMT->wavFormat.wBitsPerSample)
				{
				case 4:
					result = alGetEnumValue("AL_FORMAT_STEREO4");
					break;
				case 8:
					result = alGetEnumValue("AL_FORMAT_STEREO8");
					break;
				case 16:
					result = alGetEnumValue("AL_FORMAT_STEREO16");
					break;
				}
			}
			else if (pFMT->wavFormat.wChannels == 4 && pFMT->wavFormat.wBitsPerSample == 16)
			{
				result = alGetEnumValue("AL_FORMAT_QUAD16");
			}
			return result;
		}

		struct PcmAudioStream: public IAudioStream
		{
			int32_t pcmOffset;
			int32_t pcmSize;
			int32_t curr;
			bool	eof;
			uint8_t*pcmdata;
			int32_t pcmdatamax;
			IBlob * blob;
			// Í¨¹ý IAudioStream ¼Ì³Ð
			PcmAudioStream()
			{
				eof = false;
				pcmdatamax = 88200;
				pcmdata = new uint8_t[pcmdatamax];
			}
			virtual void Rewind() override
			{
				curr = pcmOffset;
				eof = false;
			}

			virtual void Seek(double _time) override
			{
				eof = false;
				int32_t bytes = (int32_t)(_time * this->bytesPerSec);
				int32_t bytesLeft = pcmSize - (curr - pcmOffset);
				if (bytesLeft - bytes > 0)
				{
					curr += bytes;
				}
				else
				{
					curr += bytesLeft;
					eof = true;
				}
			}
            
			virtual size_t ReadChunk( const void ** _pData) override
			{
				int32_t bytes = FRAME_BUFFER_TIME_MS / 1000.0f * this->bytesPerSec;
				bytes = bytes > pcmdatamax ? pcmdatamax : bytes;
				int32_t bytesLeft = pcmSize - (curr - pcmOffset);
				if (bytesLeft - bytes <= 0)
				{
					bytes = bytesLeft;
					eof = true;
				}
				bytes = this->blob->Read(this->pcmdata, bytes);
				this->curr += bytes;
				*_pData = pcmdata;
				return bytes;
			}

			virtual bool Eof() override
			{
				return eof;
			}

			virtual void Release() override
			{
				blob->Release();
				delete this;
			}
		};

	/*	IAudioStream * IAudioStream::FromPCM(IBlob * _blob)
		{
			// read header information
			RIFF_HEADER riffHeader;
			_blob->Read(&riffHeader, sizeof(riffHeader));
			if (memcmp(riffHeader.szRiffID, "RIFF", 4) != 0 || memcmp(riffHeader.szRiffFormat, "WAVE", 4) != 0)
			{
				return nullptr;
			}
			FMT_BLOCK fmtblock;
			_blob->Read(&fmtblock, sizeof(FMT_BLOCK));
			if (memcmp(fmtblock.szFmtID, "fmt ", 4) != 0)
			{
				return nullptr;
			}
			// fmtBlock ´óÐ¡Ö»ÓÐ16»òÕß18ÕâÁ½ÖÖ¿ÉÄÜ
			if (fmtblock.dwFmtSize == 16 || fmtblock.dwFmtSize == 18)
			{
				if (fmtblock.dwFmtSize == 18)
				{
					unsigned int addition;
					_blob->Read(&addition, sizeof(unsigned int));
				}
			}
			else
			{
				return nullptr;
			}
			//
			ALenum format = WAVEFormat2AL(&fmtblock);
			// read data blocks
			CHUNK_INFO chunkInfo;
			while (_blob->Read(&chunkInfo, sizeof(chunkInfo)) == sizeof(chunkInfo))
			{
				// get audio buffer data only
				if (memcmp(chunkInfo.szChunkID, "data", 4) == 0)
				{
					PcmAudioStream * audioStream = new PcmAudioStream();
					audioStream->format = format;
					audioStream->channels = fmtblock.wavFormat.wChannels;
					audioStream->bytesPerSec = fmtblock.wavFormat.dwAvgBytesPerSec;
					audioStream->bitsPerSample = fmtblock.wavFormat.wBitsPerSample;
					audioStream->frequency = fmtblock.wavFormat.dwSamplesPerSec;
					audioStream->curr = audioStream->pcmOffset = _blob->Tell();
					audioStream->pcmSize = chunkInfo.dwChunkSize;
					audioStream->blob = _blob;
					return audioStream;
				}
				else
				{
					// Ìø¹ýÕâÆ¬Êý¾ÝÇøÓò
					_blob->Seek(SEEK_CUR, chunkInfo.dwChunkSize);
				}
			}
			return nullptr;
		}
         */
	}
}



