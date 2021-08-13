#include "all.h"
#include <SDL2/SDL.h>
#include "scene/scene.h"
#include "asset/texture.h"

namespace ZJVL
{
	namespace Scene
	{
		class SplashScene : public Scene
		{
		public:
			SplashScene()
			{
				std::cout << "Creating Splash Scene" << std::endl;
			}

			void load() override
			{
				std::cout << "Loading Splash Scene" << std::endl;
				left_ms = 0;
				showing = false;
			};

			void unload() override
			{
				std::cout << "Loading Splash Scene" << std::endl;
			};

			void update(std::uint32_t dt) override
			{
				left_ms -= dt;
				if (left_ms <= 0)
				{
					showing = false;
					// TODO: Switch
				}
			};

			void render(SDL_Renderer *renderer) override
			{
				std::cout << "Rendering Splash Scene" << std::endl;
				SDL_RenderCopy(renderer, texture->data, NULL, NULL);
			}

			std::shared_ptr<Asset::TextureX> texture;
			bool showing;
			std::uint32_t display_ms;
			std::uint32_t left_ms;
		};
	}
}