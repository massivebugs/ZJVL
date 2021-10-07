#include "all.h"
#include <SDL2/SDL.h>
#include "game_object.h"
#include "util/vec2.h"

namespace ZJVL
{
	GameObject::GameObject(const Vec2 &pos) : pos(pos){};

	float GameObject::get_object_distance(const GameObject &other)
	{
		return (pos - other.pos).magnitude();
	}
}
