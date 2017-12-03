#include "source.h"
#include <cassert>

namespace iflib
{
	namespace openal
	{
		AL_FLOAT_GETTER SourceGetter_float = alGetSourcef;
		AL_FLOAT_SETTER SourceSetter_float = alSourcef;
		AL_FLOAT_VEC_SETTER SourceSetter_vec_float = alSourcefv;
		AL_FLOAT_GETTER SourceGetter_vec_float = alGetSourcefv;

		AL_INT32_GETTER SourceGetter_int = alGetSourcei;
		AL_INT32_SETTER SourceSetter_int = alSourcei;
		AL_INT32_VEC_SETTER SourceSetter_vec_int = alSourceiv;
		AL_INT32_GETTER SourceGetter_vec_int = alGetSourceiv;

		void Source::Play()
		{
			alSourcePlay(src);
		}

		void Source::Pause()
		{
			alSourcePause(src);
		}

		void Source::Stop()
		{
			alSourceStop(src);
		}

		void Source::Rewind()
		{
			alSourceRewind(src);
		}

		void Source::QueueBuffer(std::shared_ptr<Buffer> _buff)
		{
			CLEAR_AL_ERROR;
			alSourceQueueBuffers(src, 1, &_buff->buff);
			listBuff.push_back(_buff);
			//assert(listBuff.size() <= MAXBUFFQUEUED);
			CHECK_AL_ERROR;
		}

	/*	void Source::UnqueueBuffer(ALint _num, std::shared_ptr<Buffer>(&vecBuff_)[MAXBUFFQUEUED])
		{
			CLEAR_AL_ERROR;
			static ALbuff alBuffs[MAXBUFFQUEUED];
			alSourceUnqueueBuffers(src, _num, &alBuffs[0]);
			for (ALint i = 0; i < _num; ++i)
			{
				for (auto& buff : this->listBuff)
				{
					if (buff->buff == alBuffs[i])
					{
						vecBuff_[i] = buff;
						break;
					}
				}
			}
			CHECK_AL_ERROR;
		}*/

		void Source::UnqueueBuffer(std::shared_ptr<Buffer>& buff_)
		{
			CLEAR_AL_ERROR;
			static ALbuff alBuffs;
			alSourceUnqueueBuffers(src, 1, &alBuffs);
			CHECK_AL_ERROR;
			buff_ = listBuff.front();
			listBuff.erase(listBuff.begin());
		}

		void Source::ReloadHead( const void * _data, size_t _size, ALenum _format, ALsizei _freq)
		{
			CLEAR_AL_ERROR;
			static ALbuff alBuffs;
			alSourceUnqueueBuffers(src, 1, &alBuffs);
			CHECK_AL_ERROR;
			std::shared_ptr< Buffer > buff = listBuff.front();
			listBuff.erase(listBuff.begin());
			listBuff.push_back(buff);
			buff->BufferData(_data, _size, _format, _freq);
			alSourceQueueBuffers(src, 1, &alBuffs);
		}

		ALint Source::ProcessedBufferCount()
		{
			ALint num = -1;
			alGetSourcei(src, AL_BUFFERS_PROCESSED, &num);
			return num;
		}

		ALint Source::QueuedBufferCount()
		{
			return listBuff.size();
		/*	ALint num;
			alGetSourcei(src, AL_BUFFERS_QUEUED, &num);
			return num;*/
		}

		// micro

		AL_SOURCE_GET_SET_IMP(float, PITCH)
		AL_SOURCE_GET_SET_IMP(float, GAIN)
		AL_SOURCE_GET_SET_IMP(float, MAX_DISTANCE)
		AL_SOURCE_GET_SET_IMP(float, ROLLOFF_FACTOR)
		AL_SOURCE_GET_SET_IMP(float, REFERENCE_DISTANCE)
		AL_SOURCE_GET_SET_IMP(float, MIN_GAIN)
		AL_SOURCE_GET_SET_IMP(float, MAX_GAIN)
		AL_SOURCE_GET_SET_IMP(float, CONE_OUTER_GAIN)
		AL_SOURCE_GET_SET_IMP(float, CONE_INNER_ANGLE)
		AL_SOURCE_GET_SET_IMP(float, CONE_OUTER_ANGLE)
		AL_SOURCE_GET_SET_IMP(float, SEC_OFFSET)

		AL_SOURCE_GET_SET_IMP(int, BYTE_OFFSET)
		AL_SOURCE_GET_SET_IMP(int, SOURCE_RELATIVE)
		AL_SOURCE_GET_SET_IMP(int, SOURCE_TYPE);
		AL_SOURCE_GET_SET_IMP(int, LOOPING);
		AL_SOURCE_GET_SET_IMP(int, BUFFER);
		AL_SOURCE_GET_SET_IMP(int, SOURCE_STATE);
		AL_SOURCE_GET_SET_IMP(int, BUFFERS_QUEUED);
		AL_SOURCE_GET_SET_IMP(int, BUFFERS_PROCESSED);

		AL_SOURCE_GET_SET_VEC_IMP( float, POSITION);
		AL_SOURCE_GET_SET_VEC_IMP( float, VELOCITY);
		AL_SOURCE_GET_SET_VEC_IMP( float, DIRECTION);

	}
}

