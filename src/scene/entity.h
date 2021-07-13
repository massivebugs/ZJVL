#ifndef ZJVL_ENTITY_H
#define ZJVL_ENTITY_H

#include <cstdint>

namespace ZJVL
{
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
}

#endif