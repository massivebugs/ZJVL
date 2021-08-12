#ifndef ZJVL_CORE_SCENE_PLAYER_H
#define ZJVL_CORE_SCENE_PLAYER_H

#include "all.h"
#include "entity.h"
#include "event/observer.h"
#include "event/events/key_event.h"
#include "event/events/mouse_event.h"

namespace ZJVL
{
	namespace Scene
	{
		class Player : public Entity
		{
		public:
			Player() = default;
			Player(float x, float y, float angle, float fov) : Entity(x, y, angle, fov){};
			// Camera camera;
			virtual void on_notify(Event::Event &e) override
			{
				switch (e.get_type())
				{
				case Event::EventType::KEYDOWN:
					switch (static_cast<Event::KeyDownEvent &>(e).get_key())
					{
					case Event::Key::ENTER:
						break;
					case Event::Key::ESC:
						break;
					case Event::Key::W:
						x += std::cos(angle) * 0.1;
						y += std::sin(angle) * 0.1;
						break;
					case Event::Key::A:
						y += 0.1;
						break;
					case Event::Key::S:
						x -= std::cos(angle) * 0.1;
						y -= std::sin(angle) * 0.1;
						break;
					case Event::Key::D:
						x -= 0.1;
						break;
					}
					break;
				case Event::EventType::MOUSEMOVE:
					angle += static_cast<Event::MouseMoveEvent &>(e).x * M_PI / 360;
				}
			}
		};
	};
}

#endif