#include "all.h"
#include "core/app.h"
#include "scene/splash_scene.h"
#include "scene/game_scene.h"
#include "asset/texture.h"

// Create the app instance, init() and call run() to execute the game loop.
// Arguments and the return statement are required for compatibility with SDL
int main(int argc, char *argv[])
{
	ZJVL::Core::App *app = ZJVL::Core::App::instance();
	app->name = "Test Game";
	app->window_w = 1920;
	app->window_h = 1080;

	// The application return code
	int code = 0;

	if (app->init())
	{
		// ========= Game logic ========= //
		// auto splash_scene = std::make_shared<ZJVL::Scene::SplashScene>();
		// splash_scene->texture = app->asset_cache.get<ZJVL::Asset::Texture>("assets/splash_zjvl.png");
		// splash_scene->display_ms = 1000;

		auto game_scene = std::make_shared<ZJVL::Scene::GameScene>();
		app->scene_manager.change_to(game_scene);

		code = app->run();
	} else {
		// TODO: Initialization failed, do something here
	}

	delete app;
	return code;
}