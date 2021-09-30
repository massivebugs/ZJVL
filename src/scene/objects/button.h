// #ifndef ZJVL_SCENE_BUTTON_H
// #define ZJVL_SCENE_BUTTON_H

// #include "all.h"
// #include <SDL2/SDL.h>
// #include "game_object.h"
// #include "asset/texture.h"
// #include "core/vec2.h"

// namespace ZJVL
// {
// 	namespace Scene
// 	{
// 		class Button : public GameObject
// 		{
// 		public:
// 			Button(Util::Vec2 vec2, std::size_t w, std::size_t h) : GameObject(vec2, w, h), m_rect{vec2.x, vec2.y, w, h}
// 			{
// 				on_click_fun_ptr = nullptr;
// 				on_hover_fun_ptr = nullptr;
// 			};

// 			bool create() override {
// 				// TODO
// 			};

// 			void update(std::uint32_t dt) override{};

// 			void render(SDL_Renderer *renderer) override
// 			{
// 				SDL_RenderCopy(renderer, texture->data, NULL, NULL);
// 			};

// 			void destroy() override {
// 				// TODO
// 			};

// 			void on_notify(Event::Event &e) override{
// 			    // Hover
// 			    // Click
// 			};

// 			void on_hover(void (*fun_ptr)())
// 			{
// 				on_hover_fun_ptr = fun_ptr;
// 			};

// 			void on_click(void (*fun_ptr)())
// 			{
// 				on_click_fun_ptr = fun_ptr;
// 			};

// 			std::string label;
// 			std::shared_ptr<Asset::Texture> texture;

// 		private:
// 			void (*on_click_fun_ptr)();
// 			void (*on_hover_fun_ptr)();

// 			SDL_Rect m_rect;
// 		};
// 	}
// }

// #endif