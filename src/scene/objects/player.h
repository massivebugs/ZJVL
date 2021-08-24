#ifndef ZJVL_SCENE_SCENE_PLAYER_H
#define ZJVL_SCENE_SCENE_PLAYER_H

#include "all.h"
#include "scene/entity.h"
#include "event/observer.h"
#include "event/events/key_event.h"
#include "event/events/mouse_event.h"

namespace ZJVL
{
	class Player : public Entity
	{
	public:
		Player() = default;
		Player(float x, float y, float angle, float fov) : Entity(x, y, angle, fov){};
		// Camera camera;
		virtual void on_notify(Event &e) override
		{
			switch (e.get_type())
			{
			case EventType::KEYDOWN:
				switch (static_cast<KeyDownEvent &>(e).get_key())
				{
				case Key::ENTER:
					break;
				case Key::ESC:
					break;
				case Key::W:
					x += std::cos(angle) * 0.1;
					y += std::sin(angle) * 0.1;
					break;
				case Key::A:
					y += 0.1;
					break;
				case Key::S:
					x -= std::cos(angle) * 0.1;
					y -= std::sin(angle) * 0.1;
					break;
				case Key::D:
					x -= 0.1;
					break;
				}
				break;
			case EventType::MOUSEMOVE:
				angle += static_cast<MouseMoveEvent &>(e).x * M_PI / 360;
			}
		}
	};
}

#endif