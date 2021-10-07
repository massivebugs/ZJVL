#include "all.h"
#include "core/app.h"
#include "util/vec2.h"
#include "scene/scene.h"
#include "scene/objects/splash_image.h"
#include "scene/objects/game_map.h"
#include "scene/objects/player.h"
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

		// // Splash Scene
		// auto splash_scene = std::make_shared<ZJVL::Scene>();
		// splash_scene->set_fade(500, 500);
		// splash_scene->objects.emplace_back(std::make_shared<ZJVL::SplashImage>("assets/first_splash.jpg", 3000, "game"));

		// Game Scene
		std::shared_ptr<ZJVL::GameMap> map = std::make_shared<ZJVL::GameMap>("assets/walltext.png");
		map->x_tiles_count = 16;
		map->y_tiles_count = 16;
		map->w = 300;
		map->h = 300;
		map->pos.x = 50;
		map->pos.y = 50;
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
		auto game_scene = std::make_shared<ZJVL::Scene>();
		game_scene->objects.push_back(map);
		app->input_system.add_observer(map);

		std::shared_ptr<ZJVL::Player> player = std::make_shared<ZJVL::Player>(ZJVL::Vec2(14, 14), "assets/monsters.png");
		game_scene->objects.push_back(player);
		app->input_system.add_observer(player);

		game_scene->set_fade(500, 500);
		game_scene->camera.set_context(player);

		game_scene->objects.emplace_back(std::make_shared<ZJVL::Enemy>(ZJVL::Vec2(15, 15), "assets/monsters.png"));
		game_scene->objects.emplace_back(std::make_shared<ZJVL::Enemy>(ZJVL::Vec2(150, 150), "assets/monsters.png"));
		
		// app->scene_manager.add("splash", splash_scene);
		app->scene_manager.add("game", game_scene);
		app->scene_manager.switch_to("game");

		code = app->run();
	}
	else
	{
		// TODO: Initialization failed, do something here
	}

	delete app;
	return code;
}