#include "aldef.h"
#include "buffer.h"
#include <vector>
#include <memory>
#include <list>

#define AL_SOURCE_GET_SET_DEF( TYPE, PARAM ) \
	TYPE GET_##PARAM(); \
	void SET_##PARAM( TYPE );

#define AL_SOURCE_GET_SET_IMP( TYPE, PARAM )\
	TYPE Source::GET_##PARAM(){\
		static TYPE value;\
		SourceGetter_##TYPE( src, AL_##PARAM, &value);\
		return value;\
	}\
	void Source::SET_##PARAM( TYPE value){\
		SourceSetter_##TYPE( src, AL_##PARAM, value);\
	}\

#define AL_SOURCE_GET_SET_VEC_DEF( TYPE, PARAM )\
	void GET_##PARAM( TYPE * );\
	void SET_##PARAM( TYPE * );

#define AL_SOURCE_GET_SET_VEC_IMP(TYPE, PARAM )\
	void Source::GET_##PARAM( TYPE * _pValue){\
		SourceSetter_vec_##TYPE( src, AL_##PARAM, _pValue);\
	}\
	void Source::SET_##PARAM( TYPE * _pValue){\
		SourceGetter_vec_##TYPE( src, AL_##PARAM, _pValue);\
}\

namespace iflib
{
	namespace openal
	{
		typedef void(*AL_FLOAT_SETTER)(ALuint, ALenum, ALfloat);
		typedef void(*AL_FLOAT_GETTER)(ALuint, ALenum, ALfloat *);
		typedef void(*AL_INT32_SETTER)(ALuint, ALenum, ALint);
		typedef void(*AL_INT32_GETTER)(ALuint, ALenum, ALint *);
		typedef void(*AL_INT32_VEC_SETTER)(ALuint, ALenum, const ALint *);
		typedef void(*AL_FLOAT_VEC_SETTER)(ALuint, ALenum, const ALfloat *);

		struct Source
		{
			ALsource src;
			std::list<std::shared_ptr<Buffer>> listBuff;

			Source()
			{
				alGenSources(1, &src);
			}

			virtual void Play();
			virtual void Pause();
			virtual void Stop();
			virtual void Rewind();

			void QueueBuffer(std::shared_ptr<Buffer> _buff);
		//	void UnqueueBuffer(ALint _num, std::shared_ptr<Buffer>(&buff_)[MAXBUFFQUEUED]);
			void UnqueueBuffer(std::shared_ptr<Buffer>& buff_);
			void ReloadHead( const void * _data, size_t _size, ALenum _format, ALsizei _freq);

			ALint ProcessedBufferCount();
			ALint QueuedBufferCount();

			// micro functions
			AL_SOURCE_GET_SET_DEF(float, PITCH)
			AL_SOURCE_GET_SET_DEF(float, GAIN)
			AL_SOURCE_GET_SET_DEF(float, MAX_DISTANCE)
			AL_SOURCE_GET_SET_DEF(float, ROLLOFF_FACTOR)
			AL_SOURCE_GET_SET_DEF(float, REFERENCE_DISTANCE)
			AL_SOURCE_GET_SET_DEF(float, MIN_GAIN)
			AL_SOURCE_GET_SET_DEF(float, MAX_GAIN)
			AL_SOURCE_GET_SET_DEF(float, CONE_OUTER_GAIN)
			AL_SOURCE_GET_SET_DEF(float, CONE_INNER_ANGLE)
			AL_SOURCE_GET_SET_DEF(float, CONE_OUTER_ANGLE)
			AL_SOURCE_GET_SET_DEF(float, SEC_OFFSET)

			AL_SOURCE_GET_SET_DEF(int, BYTE_OFFSET)
			AL_SOURCE_GET_SET_DEF(int, SOURCE_RELATIVE)
			AL_SOURCE_GET_SET_DEF(int, SOURCE_TYPE);
			AL_SOURCE_GET_SET_DEF(int, LOOPING);
			AL_SOURCE_GET_SET_DEF(int, BUFFER);
			AL_SOURCE_GET_SET_DEF(int, SOURCE_STATE);
			AL_SOURCE_GET_SET_DEF(int, BUFFERS_QUEUED);
			AL_SOURCE_GET_SET_DEF(int, BUFFERS_PROCESSED);

			AL_SOURCE_GET_SET_VEC_DEF(float, POSITION);
			AL_SOURCE_GET_SET_VEC_DEF(float, VELOCITY);
			AL_SOURCE_GET_SET_VEC_DEF(float, DIRECTION);
		};
	}
}