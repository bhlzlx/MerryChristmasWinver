#pragma once
#include "aldef.h"
#include <memory>

namespace iflib
{
    namespace openal
    {
        struct Context
        {
            ALCcontext * context;
			void MakeCurrent();
			void Suspend();
			void Process();
        };
        
        struct Device
        {
            ALCdevice * device;
			Device();  
			void Release();
			std::shared_ptr<Context> CreateContext(const int * _attrlist);
        };

		std::shared_ptr<Device> GetDevice(const char * _name);
    }
}
