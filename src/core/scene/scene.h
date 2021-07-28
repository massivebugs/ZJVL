#ifndef ZJVL_CORE_SCENE_H
#define ZJVL_CORE_SCENE_H
#include "all.h"
#include "map.h"
#include "splash.h"
#include "entity.h"
#include "player.h"

namespace ZJVL
{
	namespace Core
	{
		class Scene
		{
		public:
			Scene();
			Scene(Map map, Player player, std::vector<Entity> entities);
			virtual ~Scene(){};

			bool init();
			void load();
			void update(std::uint32_t dt);
			void unload();
			void cleanup();

			void load_splash(Splash splash_image);
			void sort_entities();

			Map map;
			Player player;
			std::vector<Entity> entities;
			std::vector<Splash> splash_images;

		private:
			void sort(std::vector<Entity> &entities);
			void merge(std::vector<Entity> &l_vect, std::vector<Entity> &r_vect, std::vector<Entity> &merged);
		};
	}
}

#endif