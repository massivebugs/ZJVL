#include "all.h"
#include "entity.h"

namespace ZJVL
{
	namespace Scene
	{
		Entity::Entity(){};

		Entity::Entity(float x, float y, std::size_t texture_index)
		    : x(x), y(y), texture_index(texture_index){};

		Entity::Entity(float x, float y, float angle, float fov) : x(x), y(y), angle(angle), fov(fov){};

		bool Entity::operator<(const Entity &s) const
		{
			return dist > s.dist;
		}
	}
}
