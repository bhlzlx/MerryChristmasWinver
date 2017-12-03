#pragma once
#include "streamAudioSource.h"
#include <vector>
#include "fftw3.h"
#include <math.h>

namespace iflib
{
	namespace openal
	{
		struct FFTAnylizer
		{
			struct cplx
			{
				double r;
				double i;
			};
			StreamAudioSource * audioSource;
			IAudioStream * audioStream;
			int32_t			sampleNum;
			//
			std::vector<uint8_t> sampleData;
			std::vector<cplx> fftIn;
			std::vector<cplx> fftOut;
			//
			std::vector<float> fftArrayf;
			std::vector<float> fftArrayArtf;
			//
			fftw_plan		  fftwPlan;
		public:
			FFTAnylizer()
			{

			}
			void Init(StreamAudioSource * _audioSource, int32_t _sampleNum)
			{
				sampleNum = _sampleNum;
				audioSource = _audioSource;
				audioStream = _audioSource->audioStream;

				size_t bytesNeed = audioStream->sampleDepth * audioStream->channels * sampleNum;
				sampleData.reserve(bytesNeed);
				fftIn.reserve(sampleNum);
				fftOut.reserve(sampleNum);
				fftIn.assign(sampleNum,{ 0,0 });
				fftOut.assign(sampleNum, { 0,0 });
				sampleData.assign(bytesNeed, 0);
				//
				fftArrayf.reserve(sampleNum);
				fftArrayf.assign(sampleNum, 0.0f);
				fftArrayArtf.reserve(sampleNum);
				fftArrayArtf.assign(sampleNum, 0.0f);
				//
				fftwPlan = fftw_plan_dft_1d(sampleNum, (fftw_complex*)&fftIn[0], (fftw_complex*)&fftOut[0], FFTW_FORWARD, FFTW_ESTIMATE);
			}

			void Tick()
			{
				if (audioSource->state != StreamAudioSource::Playing)
				{
					return;
				}
				SamplingPcmData();
				RunFFT();
			}

			bool SamplingPcmData()
			{
				int processed = audioSource->ProcessedBufferCount();
				if (processed == -1)
				{
					return false;
				}
				int offset = audioSource->GET_BYTE_OFFSET();
				size_t bytes = audioStream->GetPcmSample(processed, offset, sampleNum, &sampleData[0]);
				/*if (bytes < sampleData.size())
				{
				memset( &sampleData[bytes-1],0, sampleData.size() - bytes);
				}*/
				return true;
			}

			void RunFFT()
			{
				const char * sampledPcmData = (const char*)sampleData.data();
				switch (audioStream->sampleDepth)
				{
				case 1:
				{
					for (int32_t i = 0; i < sampleNum; i++)
					{
						fftIn[i].r = ((double)sampledPcmData[i*audioStream->channels] + 256.0) / 256.0 / 2;
						//fftIn[i].r = (double)sampledPcmData[i*audioStream->channels];
						fftIn[i].i = 0.0;
					}
				}
				case 2:
				{
					const short * sampledPcmDataDW = (const short *)sampleData.data();
					for (int32_t i = 0; i < sampleNum; i++)
					{
						fftIn[i].r = ((double)sampledPcmDataDW[i*audioStream->channels] + 65536.0) / 65536.0 / 2;
						//fftIn[i].r = (double)sampledPcmDataDW[i*audioStream->channels];
						fftIn[i].i = 0.0;
					}
				}
				}
				fftw_execute(fftwPlan); /* repeat as needed*/
				for (int32_t i = 1; i < sampleNum / 2; ++i)
				{
					float waveHeight = pow(pow(fftOut[i].r, 2) + pow(fftOut[i].i, 2), 0.5);
					waveHeight = pow(waveHeight, 0.8);
					if (waveHeight > 20)
					{
						waveHeight = 20;
					}
					waveHeight /= 20;
					float realtimeWaveHeight = waveHeight *abs(cos(atan(fftOut[i].i / fftOut[i].r)));
					fftArrayf[i] -= 0.01f;
					if (fftArrayf[i] < 0)
					{
						fftArrayf[i] = 0.0f;
					}
					if (realtimeWaveHeight > fftArrayf[i])
					{
						fftArrayf[i] = realtimeWaveHeight;
					}
				}
				fftArrayf[0] = 0;
				fftArrayArtf = fftArrayf;
				for (int32_t i = 1; i < sampleNum / 2; ++i)
				{
					if (fftArrayArtf[i] > fftArrayArtf[i - 1])
					{
						fftArrayArtf[i - 1] += (fftArrayArtf[i] - fftArrayArtf[i - 1]) * 0.5;
					}
					else
					{
						fftArrayArtf[i] += (fftArrayArtf[i - 1] - fftArrayArtf[i]) * 0.5;// *pow(fftArrayArtf[i], 0.5);
					}
				}

			}

			void Release()
			{
			}
			~FFTAnylizer()
			{

			}
		};
	}
}