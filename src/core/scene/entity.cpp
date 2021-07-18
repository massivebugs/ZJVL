#include "entity.h"

namespace ZJVL
{
	namespace Core
	{
		bool Entity::operator<(const Entity &s) const
		{
			return dist > s.dist;
		}
	}
}
