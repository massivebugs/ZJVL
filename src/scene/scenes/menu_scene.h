// #ifndef ZJVL_SCENE_MENUSCENE_H
// #define ZJVL_SCENE_MENUSCENE_H

// #include "all.h"
// #include <SDL2/SDL.h>
// #include "core/app.h"
// #include "scene/scene.h"
// #include "asset/texture.h"

// namespace ZJVL
// {
// 	class MenuScene : public Scene
// 	{
// 	public:
// 		MenuScene()
// 		{
// 			std::cout << "Creating Menu Scene" << std::endl;
// 		}

// 		void load() override
// 		{
// 			std::cout << "Loading Menu Scene" << std::endl;
// 		}

// 		void unload() override
// 		{
// 			std::cout << "Unloading Menu Scene" << std::endl;
// 		}

// 		void update(std::uint32_t dt) override
// 		{
// 			for (Button button : buttons)
// 			{
// 				// Do something
// 			}
// 		}

// 		void render(SDL_Renderer *renderer) override {}

// 		std::vector<Button> buttons;
// 	};
// }

// #endif