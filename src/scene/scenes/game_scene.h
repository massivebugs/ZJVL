// #ifndef ZJVL_SCENE_GAMESCENE_H
// #define ZJVL_SCENE_GAMESCENE_H

// #include "all.h"
// #include <SDL2/SDL.h>
// #include "core/app.h"
// #include "scene/scene.h"
// #include "scene/objects/game_map.h"
// #include "scene/objects/player.h"
// #include "asset/texture.h"
// #include "asset/sprite_sheet.h"
// #include "util/vec2.h"

// namespace ZJVL
// {
// 	class GameScene : public Scene
// 	{
// 	public:
// 		GameScene(std::shared_ptr<GameMap> map);

// 		void load() override;

// 		void unload() override;

// 		void update(std::uint32_t dt) override;

// 		void render(SDL_Renderer *renderer) override;

// 	public:
// 		std::shared_ptr<GameMap> map;
// 		std::shared_ptr<GameObject> player;
// 		std::vector<std::shared_ptr<GameObject>> objects;
// 		// SpriteSheet entities_tex = SpriteSheet("assets/monsters.png");

// 	private:
// 		// std::vector<std::uint32_t> pixel_buffer;
// 		// std::size_t rect_w;
// 		// std::size_t rect_h;
// 		// std::vector<float> depth_buffer;

// 		// void draw_object(std::shared_ptr<GameObject> object);

// 		// void cast_ray();

// 		// Referenced https://github.com/ssloy/tinyraycaster
// 		// TODO: Switch to DDA Algorithm for casting rays
// 		// void draw();

// 		// void set_pixel(const std::size_t x, const std::size_t y, const std::uint32_t color);

// 		// void draw_rectangle(const std::size_t rect_x, const std::size_t rect_y, const std::size_t rect_w, const std::size_t rect_h, const std::uint32_t color);

// 		// void clear(const std::uint32_t color);

// 		// bool is_transparent_pixel(const uint32_t &color);

// 		// uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 0xFF);
// 	};
// }

// #endif