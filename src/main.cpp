#include "all.h"
#include "core/app.h"
#include "core/vec2.h"
#include "scene/scenes/splash_scene.h"
#include "scene/scenes/game_scene.h"
#include "scene/objects/game_map.h"
#include "scene/objects/enemy.h"

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
		map->w = 16;
		map->h = 16;
		map->map_data = {
			'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ','3','3','3','3',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','1',
			'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1',
		};
		auto game_scene = std::make_shared<ZJVL::GameScene>(map);

		// Register to Scene Manger
		app->scene_manager.add("splash", splash_scene);
		app->scene_manager.add("game", game_scene);
		app->scene_manager.show("splash");

		// ZJVL::Enemy enemy = ZJVL::Enemy("assets/demon_1.png", ZJVL::Vec2(3.523, 3.812));
		game_scene->actors.emplace_back(std::make_shared<ZJVL::Enemy>(ZJVL::Vec2(3.523, 3.812), "assets/monsters.png"));
		game_scene->actors.emplace_back(std::make_shared<ZJVL::Enemy>(ZJVL::Vec2(1.834, 8.765), "assets/monsters.png"));
		

		code = app->run();
	}
	else
	{
		// TODO: Initialization failed, do something here
	}

	delete app;
	return code;
}