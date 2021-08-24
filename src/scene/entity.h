#ifndef ZJVL_SCENE_ENTITY_H
#define ZJVL_SCENE_ENTITY_H

#include "all.h"
#include "event/observer.h"

namespace ZJVL
{
	class Entity : public Observer
	{
	public:
		Entity();
		Entity(float x, float y, std::size_t texture_index);
		Entity(float x, float y, float angle, float fov);
		virtual ~Entity() = default;
		float x, y;
		float angle;
		float fov;
		std::size_t texture_index;
		size_t w, h;
		float dist;

		bool operator<(const Entity &s) const;
		virtual void on_notify(Event &e) override{};

		void update(std::uint32_t dt);
	};
}

#endif