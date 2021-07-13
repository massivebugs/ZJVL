#include "core/app.h"
#include <vector>
#include "scene/scene.h"

// Args required for compatibility with SDL
int main(int argc, char *argv[])
{
	Engine::App *app = new Engine::App("Test game", 1024, 512);
	std::vector<Engine::Entity> entities = std::vector<Engine::Entity>{{3.523, 3.812, NULL, NULL, 2}, {1.834, 8.765, NULL, NULL, 0}, {5.323, 5.365, NULL, NULL, 1}, {4.123, 10.265, NULL, NULL, 2}};
	Engine::Entity player {3.456, 2.345, 1.523, M_PI / 3.};
	Engine::Map map;
	Engine::Scene scene{map, player, entities};
	scene.load_splash(Engine::Splash{"assets/splash_zjvl.png", 3000});
	app->current_scene = scene;
	int code = app->run();
	delete app;
	return code;
}