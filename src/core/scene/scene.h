// #ifndef ZJVL_CORE_SCENE_H
// #define ZJVL_CORE_SCENE_H
// #include "all.h"
// #include "map.h"
// #include "splash.h"
// #include "entity.h"
// #include "player.h"

// namespace ZJVL
// {
// 	namespace Core
// 	{
// 		class Scene
// 		{
// 		public:
// 			Scene();
// 			Scene(Map map, Player player, std::vector<Entity> entities);
// 			virtual ~Scene(){};

// 			void load_splash(Splash splash_image);
// 			void sort_entities();

// 			Map map;
// 			Player player;
// 			std::vector<Entity> entities;
// 			std::vector<Splash> splash_images;

// 			// TODO: virtualize
// 			void load();
// 			void unload();
// 			void update(std::uint32_t dt);
// 			void render();
// 		private:
// 			void sort(std::vector<Entity> &entities);
// 			void merge(std::vector<Entity> &l_vect, std::vector<Entity> &r_vect, std::vector<Entity> &merged);
// 		};
// 	}
// }

// #endif

#ifndef ZJVL_CORE_SCENE_H
#define ZJVL_CORE_SCENE_H
#include "all.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	namespace Core
	{
		class Scene
		{
			public:
				virtual ~Scene() = default;

				virtual void load() = 0;
				virtual void unload() = 0;
				virtual void update(std::uint32_t dt) = 0;
				virtual void render(SDL_Renderer *renderer) = 0;
		};
	}
}
#endif