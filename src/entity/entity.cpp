#include "entity.h"

bool Entity::operator < (const Entity& s) const {
	return dist > s.dist;
}