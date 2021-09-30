#include "all.h"
#include "texture.h"
#include "core/app.h"

namespace ZJVL
{
    Texture::Texture(int w, int h) : w(w), h(h)
    {
        data = SDL_CreateTexture(App::instance()->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);

        if (data == nullptr)
        {
            std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
            return;
        }
    }

    Texture::Texture(const std::string &path)
    {
        data = IMG_LoadTexture(App::instance()->renderer, path.c_str());

        if (data == nullptr)
        {
            std::cout << "Failed to load texture data . SDL_ERROR: " << SDL_GetError() << std::endl;
            return;
        }

        SDL_QueryTexture(data, nullptr, nullptr, &w, &h);
    }

    Texture::~Texture()
    {
        SDL_DestroyTexture(data);
    }

    void Texture::set_blending(SDL_BlendMode blending)
    {
        SDL_SetTextureBlendMode(data, blending);
    };

    void Texture::set_alpha(std::uint8_t a)
    {
        SDL_SetTextureAlphaMod(data, a);
    }

    void Texture::lock()
    {
        // TODO: Change
        void *temp_pixels;
        // TODO: Error handling
        SDL_LockTexture(data, NULL, &temp_pixels, &pitch);
        pixels = (std::uint32_t *)temp_pixels;
    }

    void Texture::unlock()
    {
        SDL_UnlockTexture(data);
        pixels = nullptr;
        pitch = 0;
    }
}