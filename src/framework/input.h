#ifndef ZJVL_FRAMEWORK_INPUT_H
#define ZJVL_FRAMEWORK_INPUT_H

#include <SDL2/SDL.h>
#include "core/event/subject.h"
namespace ZJVL
{
	namespace Framework
	{
		class Input: public Core::Subject
		{
		public:
			void init();
			void poll_events();

		private:
		};
	}
}

#endif