#pragma once
#include "aldef.h"

namespace iflib
{
    namespace openal
    {        
        struct Buffer
        {
            ALuint		buff;
            ALsizei		freq;
            ALsizei		size;
			ALenum		format;
            /*
            AL_FREQUENCY
            AL_BITS
            AL_CHANNELS
            AL_SIZE
            AL_DATA*/

			Buffer()
			{
			}

			void Init();

			void BufferData(const void * _data, uint32_t _size, ALenum _format, ALsizei _freq);

			ALboolean Valid();

			ALsizei Size();

			static void Dt(Buffer * _buffer)
			{
				if (_buffer->buff)
				{
					alDeleteBuffers(1, &_buffer->buff);
				}
				delete _buffer;
			}
        };
    }
}
