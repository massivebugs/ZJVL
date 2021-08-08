#include "all.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "core/event/events/window_event.h"
#include "core/event/events/key_event.h"
#include "core/event/events/mouse_event.h"

namespace ZJVL
{
	namespace Framework
	{
		Window::Window(const char *name, int w, int h) : m_keymap{
								     {SDLK_KP_ENTER, Core::Key::ENTER},
								     {SDLK_ESCAPE, Core::Key::ESC},
								     {SDLK_w, Core::Key::W},
								     {SDLK_a, Core::Key::A},
								     {SDLK_s, Core::Key::S},
								     {SDLK_d, Core::Key::D},
								 }

		{
			m_name = name;
			m_width = w;
			m_height = h;

			m_window = nullptr;
			m_renderer = nullptr;
			m_texture = nullptr;
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
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

		void Window::update()
		{
			while (SDL_PollEvent(&m_event))
			{
				if (m_event.type == SDL_QUIT)
				{
					Core::WindowCloseEvent e;
					notify(e);
				}
				input_manager.on_event(m_event);
			}
			// We only need to update mouse once per tick
			input_manager.update_mouse();
		}

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