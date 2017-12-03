#pragma once
#include "aldef.h"
#include "device.h"
#include "buffer.h"
#include "source.h"
#include "audiostream.h"
#include <vector>

namespace iflib
{
	namespace openal
	{
		typedef uint8_t byte;
		struct StreamAudioSource:public Source
		{
			enum
			{
				IdleState,
				Playing,
				Paused,
				Stopped,
			} state;
			IAudioStream * audioStream;
			bool loop;
			//
			// Functions
			StreamAudioSource();
			void Init(IAudioStream * _audioStream);
			bool Tick();
			void Seek(double _time);
			size_t GetPcmSample(uint8_t * data_, size_t _samples);
			// virtual functions
			virtual void Play();
			virtual void Pause();
			virtual void Stop();
			virtual void Rewind();
		};
	}
}

