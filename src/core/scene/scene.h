#ifndef ZJVL_CORE_SCENE_H
#define ZJVL_CORE_SCENE_H
#include <vector>
#include "scene.h"
#include "map.h"
#include "splash.h"
#include "entity.h"

namespace ZJVL
{
	namespace Core
	{
		class Scene
		{
		public:
			Scene();
			Scene(Map map, Entity player, std::vector<Entity> entities);

			bool is_activated();

			Map map;
			Entity player;
			std::vector<Entity> entities;
			std::vector<Splash> splash_images;

			void load_splash(Splash splash_image);
			void sort_entities();

		private:
			void sort(std::vector<Entity> &entities);
			void merge(std::vector<Entity> &l_vect, std::vector<Entity> &r_vect, std::vector<Entity> &merged);
			bool m_activated;
		};

	}
}

#endif