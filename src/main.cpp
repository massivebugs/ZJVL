#include "all.h"
#include "core/app.h"
#include "scene/scenes/splash_scene.h"
#include "scene/scenes/game_scene.h"
#include "asset/assets/texture.h"

// Create the app instance, init() and call run() to execute the game loop.
// Arguments and the return statement are required for compatibility with SDL
int main(int argc, char *argv[])
{
	ZJVL::App *app = ZJVL::App::instance();
	app->name = "ZJVL Raycaster";
	app->window_w = 1024;
	app->window_h = 512;

	// The application return code
	int code = 0;

	if (app->init())
	{
		// ========= Game logic ========= //

		// Splash Scene
		auto splash_scene = std::make_shared<ZJVL::SplashScene>();
		splash_scene->texture = app->asset_cache.get<ZJVL::Texture>("assets/first_splash.jpg");
		splash_scene->display_ms = 3000;
		splash_scene->next_scene_id = "game";
		splash_scene->set_fading(500, 500);

		// Game Scene
		auto game_scene = std::make_shared<ZJVL::GameScene>();

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