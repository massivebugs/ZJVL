#include "entity.h"

namespace Engine
{
	bool Entity::operator<(const Entity &s) const
	{
		return dist > s.dist;
	}
}
