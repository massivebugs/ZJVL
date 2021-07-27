#ifndef ZJVL_CORE_SCENE_CAMERA_H
#define ZJVL_CORE_SCENE_CAMERA_H
#include "core/event/observer.h"
#include "core/event/events/mouse_event.h"

namespace ZJVL
{
	namespace Core
	{
		class Camera : public Observer
		{
		public:
			Camera() : angle(0), fov(3.14159 / 3.f){};
			Camera(float initial_dir, float fov) : angle(initial_dir), fov(fov){};
			float angle;
			float fov;
			virtual void on_notify(Core::Event &e) override
			{
				switch (e.get_type())
				{
				case Core::EventType::MOUSEMOVE:
					angle += static_cast<Core::MouseMoveEvent &>(e).x * 3.141592 / 360;
				}
			}
		};
	}
}
#endif