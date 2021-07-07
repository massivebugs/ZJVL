#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>

class Entity
{
public:
	float x, y;
	float angle;
	float fov;
	std::size_t texture_index;
	size_t w, h;
	float dist;
	bool operator<(const Entity &s) const;
};

#endif