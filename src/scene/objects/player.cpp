#include "all.h"
#include "player.h"
#include "util/vec2.h"
#include "scene/actor.h"
#include "event/event.h"
#include "event/key_event.h"
#include "event/mouse_event.h"

namespace ZJVL
{
	Player::Player(const Vec2 &pos, const std::string &texture_path)
		: Actor(pos, texture_path){};

	bool Player::create(const Scene &scene) { return true; };
	void Player::update(const Scene &scene, std::uint32_t dt){};
	void Player::render(const Scene &scene, SDL_Renderer *renderer){};
	void Player::destroy(){};

	void Player::on_notify(Event &e)
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
}