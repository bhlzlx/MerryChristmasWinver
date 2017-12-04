#pragma once
#include <al/al.h>
#include <al/alc.h>
#include <stdint.h>
#include <list>
#include <string>
#include <memory.h>

namespace iflib
{
	struct IBlob;
	namespace openal
	{
		struct IAudioStream
		{
			enum eStreamState : ALenum
			{
				Closed = 0,
				Opened,
				EndOfFile,
			};

		//	ALenum			state;
			ALenum			format;
			ALsizei			frequency;
			ALsizei			channels;
			int32_t			bitsPerSample;
			int32_t			bytesPerSec;
			int32_t			sampleDepth;
			//
			uint8_t*		pcmFrame;
			int32_t			pcmFramesize;
			int32_t			pcmFramecount;

			std::string		strTitle;

			struct PcmBuff
			{
				uint8_t * data;
				uint32_t  size;
			};
			std::list<PcmBuff> listPcmBuff;

			IAudioStream()
			{
				pcmFramesize = 32 * 1024;
				pcmFrame = nullptr;
				pcmFramecount = 0;
			}

			size_t GetPcmSample(int _nSkip, size_t _offset, size_t _samples, uint8_t* data_)
			{
					auto iter = listPcmBuff.begin();
				
				// ÔçÈ¡Ò»¸ö£¡
				++iter;
				while (iter->size < _offset && iter != listPcmBuff.end())
				{
					_offset -= iter->size;
					++iter;
				}
				/*for (int i = 0; i < _nSkip; ++i)
				{
					_offset -= iter->size;
					++iter;
				}*/
				size_t bytesNeed = sampleDepth * channels * _samples;
				size_t bytesCopied = 0;
				while (iter != listPcmBuff.end() && bytesNeed )
				{
					uint8_t* samplerPos = iter->data + _offset;
					size_t left = iter->size - _offset;
					if (left >= bytesNeed)
					{
						memcpy(data_ + bytesCopied, samplerPos, bytesNeed);
						bytesCopied += bytesNeed;
						bytesNeed = 0;
						break;
					}
					else
					{
						memcpy(data_ + bytesCopied, samplerPos, left);
						bytesCopied += left;
						bytesNeed -= left;
						++iter;
						_offset = 0;
					}
				}
				return bytesCopied;
			}
			/* imp virtual */
			virtual ALsizei	Frequency()
			{
				return frequency;
			}
			virtual ALenum	Format()
			{
				return format;
			}
			virtual void Rewind() = 0;
			virtual void Seek(double _time) = 0;
			virtual float TimeCurr() = 0;
			virtual float TimeTotal() = 0;
			virtual const std::string& GetTitle()
			{
				return strTitle;
			}
			virtual void SetTitle(const std::string& _title)
			{
				strTitle = _title;
			}
			
			virtual size_t ReadChunk(const void** _pData)
			{
				auto pcmBuff = listPcmBuff.front();
				listPcmBuff.pop_front();
				//
				pcmFrame = pcmBuff.data;
				pcmBuff.size = __ReadChunk(pcmFrame);
				*_pData = pcmFrame;

				listPcmBuff.push_back(pcmBuff);
				return pcmBuff.size;
			}
			
			virtual size_t __ReadChunk(void * _pData) = 0;
			
			virtual bool Eof() = 0;
			/* pure virtual */
			virtual void Release() = 0;
			/* static contruction functions */
			static IAudioStream* FromPCM(IBlob * _blob);
			static IAudioStream* FromOGG(IBlob * _blob);
			static IAudioStream* FromMP3(IBlob * _blob);

			virtual ~IAudioStream()
			{
				if (pcmFrame)
				{
					delete[]pcmFrame;
				}
			}
		};
	}
}