#include "all.h"
#include <SDL2/SDL.h>
#include "core/scene/scene.h"
#include "core/scene/splash.h"

class SplashScene : public ZJVL::Core::Scene
{
public:
	SplashScene(SDL_Renderer &renderer) : ZJVL::Core::Scene(renderer){};

	virtual void load()
	{
		std::cout << "Loading Splash Scene" << std::endl;
	};

	virtual void unload()
	{
		std::cout << "Loading Splash Scene" << std::endl;
	};

	virtual void update(std::uint32_t dt){};

	virtual void render() {}

	std::shared_ptr<ZJVL::Core::Splash> splash;
	std::uint32_t display_ms;
};