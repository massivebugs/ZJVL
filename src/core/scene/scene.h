#ifndef ZJVL_CORE_SCENE_H
#define ZJVL_CORE_SCENE_H
#include <vector>
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

			bool init();
			void load();
			void update(std::uint32_t dt);
			void unload();
			void cleanup();

			void load_splash(Splash splash_image);
			void sort_entities();

			Map map;
			Entity player;
			std::vector<Entity> entities;
			std::vector<Splash> splash_images;

		private:
			void sort(std::vector<Entity> &entities);
			void merge(std::vector<Entity> &l_vect, std::vector<Entity> &r_vect, std::vector<Entity> &merged);
		};
	}
}

#endif