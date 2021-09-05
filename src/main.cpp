#include "all.h"
#include "core/app.h"
#include "core/vec2.h"
#include "scene/scenes/splash_scene.h"
#include "scene/scenes/game_scene.h"
#include "scene/objects/game_map.h"

// Create the app instance, init() and call run() to execute the game loop.
// Arguments and the return statement are required for compatibility with SDL
int main(int argc, char *argv[])
{
	ZJVL::App *app = ZJVL::App::instance();

	// The application return code
	int code = 0;

	if (app->init("ZJVL Raycaster", 1024, 512))
	{
		// ========= Game logic ========= //

		// Splash Scene
		auto splash_scene = std::make_shared<ZJVL::SplashScene>("assets/first_splash.jpg", 3000, "game");
		splash_scene->set_fading(500, 500);

		// Game Scene
		std::shared_ptr<ZJVL::GameMap> map = std::make_shared<ZJVL::GameMap>("assets/walltext.png");
		map->pos = ZJVL::Vec2();
		map->w = 16;
		map->h = 16;
		auto game_scene = std::make_shared<ZJVL::GameScene>(map);

		// Register to Scene Manger
		app->scene_manager.add("splash", splash_scene);
		app->scene_manager.add("game", game_scene);

		app->scene_manager.show("splash");

		code = app->run();

	} else {
		// TODO: Initialization failed, do something here

	}

	delete app;
	return code;
}