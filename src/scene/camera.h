#ifndef ZJVL_SCENE_CAMERA_H
#define ZJVL_SCENE_CAMERA_H

#include "event/observer.h"
#include "event/events/mouse_event.h"

namespace ZJVL
{
	namespace Scene
	{
		class Camera : public Event::Observer
		{
		public:
			Camera() : angle(0), fov(3.14159 / 3.f){};
			Camera(float initial_dir, float fov) : angle(initial_dir), fov(fov){};
			float angle;
			float fov;
			virtual void on_notify(Event::Event &e) override
			{
				switch (e.get_type())
				{
				case Event::EventType::MOUSEMOVE:
					angle += static_cast<Event::MouseMoveEvent &>(e).x * 3.141592 / 360;
				}
			}
		};
	}
}
#endif