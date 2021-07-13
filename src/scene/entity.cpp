#include "entity.h"

namespace ZJVL
{
	bool Entity::operator<(const Entity &s) const
	{
		return dist > s.dist;
	}
}
