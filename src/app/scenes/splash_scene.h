#include "all.h"
#include <SDL2/SDL.h>
#include "core/scene/scene.h"
#include "core/scene/splash.h"
#include "core/core/texture.h"

class SplashScene : public ZJVL::Core::Scene
{
public:
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

		// TODO: not a solution yet but
		// SDL_Delay(display_ms);
	}

	std::shared_ptr<ZJVL::Core::TextureX> texture;
	bool showing;
	std::uint32_t display_ms;
	std::uint32_t left_ms;
};