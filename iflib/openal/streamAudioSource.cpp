#include "StreamAudioSource.h"
#include <assert.h>
#include <Windows.h>

namespace iflib
{
	namespace openal
	{
		StreamAudioSource::StreamAudioSource()
		{
			audioStream = nullptr;
			loop = false;
		}

		void StreamAudioSource::Init(IAudioStream * _audioStream)
		{
			audioStream = _audioStream;
			if (listBuff.size())
			{
				int frameCount = _audioStream->pcmFramecount;
				int listBuffCount = listBuff.size();
				Source::Play();
				while (true)
				{
					Sleep(100);
					if (ProcessedBufferCount() == listBuffCount)
					{
						break;
					}
				}
				// 现在的Pcm framecount和之前的 stream对应的可能不一样,但是现在存的还是之前的framecount
				if (listBuffCount > frameCount)
				{
					for (size_t i = 0; i < listBuffCount - frameCount; ++i)
					{
						std::shared_ptr<Buffer> buffer;
						UnqueueBuffer(buffer);
					}
					listBuffCount = frameCount;
				}
				for (int32_t i = 0; i < listBuffCount; ++i)
				{
					const void * chunk = nullptr;
					size_t size = _audioStream->ReadChunk(&chunk);
					std::shared_ptr<Buffer> buffer; 
					UnqueueBuffer(buffer);
					buffer->BufferData(chunk, size, audioStream->format, audioStream->frequency);
					QueueBuffer(buffer);
					if (_audioStream->Eof())
					{
						break;
					}
				}
				while(listBuffCount < frameCount)
				{
					const void * chunk = nullptr;
					size_t size = _audioStream->ReadChunk(&chunk);
					std::shared_ptr<Buffer> buffer(new Buffer(), Buffer::Dt);
					buffer->Init();
					buffer->BufferData(chunk, size, audioStream->format, audioStream->frequency);
					QueueBuffer(buffer);
					if (_audioStream->Eof())
					{
						break;
					}
					++listBuffCount;
				}

				if (!_audioStream->Eof())
				{
					while (listBuffCount < frameCount)
					{
						const void * chunk = nullptr;
						size_t size = _audioStream->ReadChunk(&chunk);
						std::shared_ptr<Buffer> buffer(new Buffer(), Buffer::Dt);
						buffer->Init();
						buffer->BufferData(chunk, size, audioStream->format, audioStream->frequency);
						QueueBuffer(buffer);
						if (_audioStream->Eof())
						{
							break;
						}
						++listBuffCount;
					}
				}
			}
			else
			{
				for (int32_t i = 0; i < _audioStream->pcmFramecount; ++i)
				{
					const void * chunk = nullptr;
					size_t size = _audioStream->ReadChunk(&chunk);
					std::shared_ptr<Buffer> buffer(new Buffer(), Buffer::Dt);
					buffer->Init();
					buffer->BufferData(chunk, size, audioStream->format, audioStream->frequency);
					QueueBuffer(buffer);
					if (_audioStream->Eof())
					{
						break;
					}
				}
			}
		}

		bool StreamAudioSource::Tick()
		{
			if (state != Playing)
				return true;
			if (!audioStream->Eof())
			{
				ALint idle = ProcessedBufferCount();
				ALint queuedSize = QueuedBufferCount();
				for (ALint i = 0; i < idle; ++i)
				{
					// Version 1
					std::shared_ptr< Buffer > buff;
					UnqueueBuffer(buff);
					assert(buff);
					const void * dataChunk;
					size_t size = audioStream->ReadChunk(&dataChunk);
					buff->BufferData(dataChunk, size, audioStream->format, audioStream->frequency);
					QueueBuffer(buff);
					/*
					// Version 2
					std::shared_ptr< Buffer > buff;
					const void * dataChunk;
					size_t size;
					size = audioStream->ReadChunk(&dataChunk);
					ReloadHead(dataChunk, size, audioStream->format, audioStream->frequency);
					*/
					if (audioStream->Eof())
					{
						break;
					}
				}
				return true;
			}
			else
			{
				auto queued = QueuedBufferCount();
				auto played = ProcessedBufferCount();
				if (queued == played)
				{
					if (loop)
					{
						Rewind();
					}
					else
					{
						return false;
					}
				}
				return true;
			}
		}

		void StreamAudioSource::Play()
		{
			Source::Play();
			state = Playing;
		}

		void StreamAudioSource::Pause()
		{
			Source::Pause();
			state = Paused;
		}

		void StreamAudioSource::Rewind()
		{
			Source::Stop();
			Seek(0.0);
			Source::Play();
			state = Playing;
		}

		void StreamAudioSource::Seek(double _time)
		{
			audioStream->Seek(_time);
			// buff全部取出来重新填
			std::vector< std::shared_ptr<Buffer> > vecBuff;
			size_t buffCnt = QueuedBufferCount();
			for (size_t i = 0; i < buffCnt; ++i)
			{
				std::shared_ptr<Buffer> buff;
				UnqueueBuffer(buff);
				vecBuff.push_back(buff);
			}
			// 填buff
			for (auto& buff : vecBuff)
			{
				const void * dataChunk;
				size_t size;
				size = audioStream->ReadChunk(&dataChunk);
				buff->BufferData(dataChunk, size, audioStream->format, audioStream->frequency);
				QueueBuffer(buff);
				if (audioStream->Eof())
				{
					break;
				}
			}
		}

		size_t StreamAudioSource::GetPcmSample(uint8_t * data_, size_t _samples)
		{
			int processed = ProcessedBufferCount();
			int offset = GET_BYTE_OFFSET();
			return audioStream->GetPcmSample(processed, offset, _samples, data_);
		}

		void StreamAudioSource::Stop()
		{
			Source::Stop();
			Seek(0.0);
			state = Stopped;
		}
	}
}