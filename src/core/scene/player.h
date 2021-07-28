#ifndef ZJVL_CORE_SCENE_PLAYER_H
#define ZJVL_CORE_SCENE_PLAYER_H

#include "all.h"
#include "entity.h"
#include "core/event/observer.h"
#include "core/event/events/key_event.h"
#include "core/event/events/mouse_event.h"

namespace ZJVL
{
	namespace Core
	{
		class Player : public Entity
		{
		public:
			Player() = default;
			Player(float x, float y, float angle, float fov) : Entity(x, y, angle, fov){};
			// Camera camera;
			virtual void on_notify(Core::Event &e) override
			{
				switch (e.get_type())
				{
				case Core::EventType::KEYDOWN:
					switch (static_cast<Core::KeyDownEvent &>(e).get_key())
					{
					case Core::Key::ENTER:
						break;
					case Core::Key::ESC:
						break;
					case Core::Key::W:
						x += std::cos(angle) * 0.1;
						y += std::sin(angle) * 0.1;
						break;
					case Core::Key::A:
						y += 0.1;
						break;
					case Core::Key::S:
						x -= std::cos(angle) * 0.1;
						y -= std::sin(angle) * 0.1;
						break;
					case Core::Key::D:
						x -= 0.1;
						break;
					}
					break;
				case Core::EventType::MOUSEMOVE:
					angle += static_cast<Core::MouseMoveEvent &>(e).x * M_PI / 360;
				}
			}
		};
	};
}

#endif