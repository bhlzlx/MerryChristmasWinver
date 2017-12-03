#include "buffer.h"
#include <assert.h>

namespace iflib
{
	namespace openal
	{
		void Buffer::Init()
		{
			CLEAR_AL_ERROR;
			alGenBuffers(1, &buff);
			CHECK_AL_ERROR;
		}

		void Buffer::BufferData( const void * _data, uint32_t _size, ALenum _format, ALsizei _freq)
		{
			CLEAR_AL_ERROR;
			alBufferData(buff, _format, _data, _size, _freq);
			freq = _freq;
			size = _size;
			format = _format;
			CHECK_AL_ERROR;
		}

		ALboolean Buffer::Valid()
		{
			return alIsBuffer(buff);
		}

		ALsizei Buffer::Size()
		{
			return size;
		}

	}
}

