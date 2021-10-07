#include "all.h"
#include <SDL2/SDL.h>
#include "actor.h"
#include "game_object.h"
#include "util/vec2.h"

namespace ZJVL
{
	Actor::Actor(const Vec2 &pos, const std::string &texture_path)
		: texture(texture_path),
		  GameObject(pos)
	{
		angle = 0;
		fov = M_PI / 3.f;
	};
}
