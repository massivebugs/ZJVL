#ifndef ZJVL_SCENE_SCENE_PLAYER_H
#define ZJVL_SCENE_SCENE_PLAYER_H

#include "all.h"
#include "core/vec2.h"
#include "scene/actor.h"
#include "event/observer.h"
#include "event/key_event.h"
#include "event/mouse_event.h"

namespace ZJVL
{
	class Player : public Actor
	{
	public:
		Player(const Vec2 &pos, const std::string &texture_path)
			: Actor(pos, texture_path){};

		bool create(const Scene &scene) { return true; };
		void update(const Scene &scene, std::uint32_t dt){};
		void render(SDL_Renderer *renderer){};
		void destroy(){};

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
					pos.x += std::cos(angle) * 0.1;
					pos.y += std::sin(angle) * 0.1;
					break;
				case Key::A:
					pos.y += 0.1;
					break;
				case Key::S:
					pos.x -= std::cos(angle) * 0.1;
					pos.y -= std::sin(angle) * 0.1;
					break;
				case Key::D:
					pos.x -= 0.1;
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