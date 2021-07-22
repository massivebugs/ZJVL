#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "core/event/window_event.h"
#include "core/event/key_event.h"

namespace ZJVL
{
	namespace Framework
	{
		Window::Window(const char *name, int w, int h)
		{
			m_name = name;
			m_width = w;
			m_height = h;

			m_window = nullptr;
			m_renderer = nullptr;
			m_texture = nullptr;

		}

		void Window::get_mouse()
		{
			SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
		}

		bool Window::init()
		{
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
			{
				std::cout << "Failed to initialize SDL. SDL ERROR: " << SDL_GetError() << std::endl;
				return false;
			}

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			{
				std::cout << "Failed to initialize SDL_image. SDL ERROR: " << SDL_GetError() << std::endl;
				return false;
			}

			// Additional SDL configurations
			SDL_SetRelativeMouseMode(SDL_TRUE);

			// Initialize SDL window
			m_window = SDL_CreateWindow(
			    m_name,
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    m_width,
			    m_height,
			    SDL_WINDOW_SHOWN);

			if (m_window == nullptr)
			{
				std::cout << "Failed to create SDL Window. SDL_ERROR: " << SDL_GetError() << std::endl;
				return false;
			}

			// Initialize SDL renderer
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_UpdateWindowSurface(m_window);

			// Initialize SDL texture
			// https: //stackoverflow.com/questions/21007329/what-is-an-sdl-renderer
			// ABGR might be faster than RGBA
			m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
			return true;
		}

		bool Window::draw(void *buffer, int row_bytes)
		{
			// TODO: Error checking
			SDL_UpdateTexture(m_texture, NULL, buffer, row_bytes);
			SDL_RenderClear(m_renderer);
			SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
			SDL_RenderPresent(m_renderer);

			return true;
		}

		bool Window::flash_image(const char *img_path, uint32_t ms)
		{
			SDL_Texture *splash_texture = nullptr;
			SDL_Surface *splash_surface = nullptr;

			// Display splashes here
			splash_surface = IMG_Load(img_path);
			if (splash_surface == nullptr)
			{
				std::cout << "Failed to load splash image . SDL_ERROR: " << SDL_GetError() << std::endl;
				return false;
			}
			splash_texture = SDL_CreateTextureFromSurface(m_renderer, splash_surface);
			if (splash_texture == nullptr)
			{
				std::cout << "Failed to load splash image . SDL_ERROR: " << SDL_GetError() << std::endl;
			}

			SDL_RenderClear(m_renderer);
			SDL_RenderCopy(m_renderer, splash_texture, NULL, NULL);
			SDL_RenderPresent(m_renderer);

			SDL_Delay(ms);

			SDL_FreeSurface(splash_surface);
			SDL_DestroyTexture(splash_texture);
			return true;
		}

		//  Window::poll_event(std::shared_ptr<Core::Event> e)
		// {
		// 	if (SDL_PollEvent(&m_event))
		// 	{
		// 		switch (m_event.type)
		// 		{
		// 		case SDL_QUIT:
		// 			e = std::make_shared<Core::WindowEvent>();
		// 			break;
		// 		case SDL_KEYDOWN:
		// 			switch (m_event.key.keysym.sym)
		// 			{
		// 			case SDLK_KP_ENTER:
		// 				e = std::make_shared<Core::KeyDownEvent>(Core::Key::ENTER);
		// 				break;
		// 			case SDLK_ESCAPE:
		// 				e = std::make_shared<Core::KeyDownEvent>(Core::Key::ESC);
		// 				break;
		// 			case SDLK_w:
		// 				e = std::make_shared<Core::KeyDownEvent>(Core::Key::W);
		// 				break;
		// 			case SDLK_a:
		// 				e = std::make_shared<Core::KeyDownEvent>(Core::Key::A);
		// 				break;
		// 			case SDLK_s:
		// 				e = std::make_shared<Core::KeyDownEvent>(Core::Key::S);
		// 				break;
		// 			case SDLK_d:
		// 				e = std::make_shared<Core::KeyDownEvent>(Core::Key::D);
		// 				break;
		// 			}
		// 			default:
		// 				e = std::make_shared<Core::Event>(Core::EventType::NONE);
		// 		}
		// 		return true;
		// 	}
		// 	return false;
		// }

		void Window::cleanup()
		{
			SDL_DestroyTexture(m_texture);
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			IMG_Quit();
			SDL_Quit();
		}
	}
}