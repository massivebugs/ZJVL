#ifndef ZJVL_CORE_ENTITY_H
#define ZJVL_CORE_ENTITY_H

#include <cstdint>
#include "core/event/observer.h"

namespace ZJVL
{
	namespace Core
	{
		class Entity : public Observer
		{
		public:
			Entity();
			Entity(float x, float y, std::size_t texture_index);
			Entity(float x, float y, float angle, float fov);
			float x, y;
			float angle;
			float fov;
			std::size_t texture_index;
			size_t w, h;
			float dist;
			bool operator<(const Entity &s) const;
			// void on_load(){};
			// void on_update(){};
			// void on_cleanup(){};
			void on_notify(Core::Event &e) override {};
		};
	}
}

#endif