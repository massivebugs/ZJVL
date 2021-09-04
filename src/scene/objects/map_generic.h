#ifndef ZJVL_SCENE_MAP_H
#define ZJVL_SCENE_MAP_H

#include "all.h"
#include <SDL2/SDL.h>
#include "asset/assets/texture.h"
#include "scene/game_object.h"
#include "event/event.h"
#include "core/vec2.h"

namespace ZJVL
{
    class Map : public GameObject
    {
    public:
        virtual ~Map() = default;

        virtual bool create() = 0;
        virtual void update(std::uint32_t dt) = 0;
        virtual void render(SDL_Renderer *renderer) = 0;
        virtual void destroy() = 0;

        virtual void on_notify(Event &e) = 0;

        int get_sprite_index(const std::size_t row, const std::size_t col);

        bool is_empty(const std::size_t row, const std::size_t col);

    public:
        std::unique_ptr<Texture> texture;
        std::vector<std::uint8_t> properties;
        std::vector<std::uint32_t> sprites;
        bool toggled = true;
    };
}

#endif