#ifndef ZJVL_CORE_ASSET_MANAGER_H
#define ZJVL_CORE_ASSET_MANAGER_H

#include "all.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// TODO: Use a string as set id, so you can reuse it
namespace ZJVL
{
	namespace Core
	{
		class AssetManager
		{
		public:
			std::uint32_t load_image(const char *path)
			{
				SDL_Surface *img_data = nullptr;
				SDL_Surface *optimized_img_data = nullptr;

				img_data = IMG_Load(path);

				if (img_data == nullptr)
				{
					std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
					return 0;
				}

				// Flags are unused
				optimized_img_data = SDL_ConvertSurfaceFormat(img_data, SDL_PIXELFORMAT_ABGR8888, 0);
				SDL_FreeSurface(img_data);

				if (optimized_img_data == nullptr)
				{
					std::cout << "Failed to format texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
					return 0;
				}

				m_images[++latest_id] = optimized_img_data;
			};

			bool has_image(std::uint32_t id)
			{
				return (m_images.find(id) == m_images.end()) == false;
			};

			SDL_Surface *get_image(std::uint32_t id)
			{
				has_image(id) ? m_images[id] : nullptr;
			};

			bool remove_image(std::uint32_t id)
			{
				if (has_image(id))
				{
					SDL_FreeSurface(m_images[id]);
					m_images.erase(id);
				}
			}

		private:
			std::uint32_t latest_id = 0;
			std::unordered_map<std::uint32_t, SDL_Surface *> m_images;
		};
	}
}

#endif