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
				shown_ms = 0;
			};

			void unload() override
			{
				std::cout << "Loading Splash Scene" << std::endl;
			};

			void update(std::uint32_t dt) override
			{
				shown_ms += dt;
				if (shown_ms >= display_ms)
				{
					// TODO: Switch
				}
			};

			void render(SDL_Renderer *renderer) override
			{
				std::cout << "Rendering Splash Scene" << std::endl;
				SDL_RenderCopy(renderer, texture->data, NULL, NULL);
			}

			std::shared_ptr<Asset::Texture> texture;
			std::uint32_t display_ms;
			std::uint32_t shown_ms;
		};
	}
}