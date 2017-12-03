#include "device.h"

namespace iflib
{
	namespace openal
	{
		void Context::MakeCurrent()
		{
			alcMakeContextCurrent(context);
		}

		void Context::Suspend()
		{
			alcSuspendContext(context);
		}

		void Context::Process()
		{
			alcProcessContext(context);
		}

		Device::Device()
		{
			device = nullptr;
		}

		void Device::Release()
		{
			alcCloseDevice(device);
		}

		std::shared_ptr<Context> Device::CreateContext(const int * _attrlist)
		{
			std::shared_ptr< Context > context;
			ALCcontext * ctx = alcCreateContext(device, _attrlist);
			if (ctx)
			{
				context.reset(new Context);
				context->context = ctx;
			}
			return context;
		}

		std::shared_ptr<Device> GetDevice(const char * _name)
		{
			std::shared_ptr<Device> device;
			ALCdevice * alcDvc = alcOpenDevice(_name);
			if (alcDvc)
			{
				device.reset(new Device);
				device->device = alcDvc;
			}
			return device;
		}

	}
}

