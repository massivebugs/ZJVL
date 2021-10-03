#ifndef ZJVL_SCENE_GAMEMAP_H
#define ZJVL_SCENE_GAMEMAP_H

#include "all.h"
#include <SDL2/SDL.h>
#include "core/vec2.h"
#include "scene/game_object.h"
#include "scene/scene.h"
#include "event/event.h"
#include "asset/sprite_sheet.h"

namespace ZJVL
{
    class GameMap : public GameObject, public Observer
    {
    public:
        GameMap(std::string sprite_sheet);

        virtual bool create(const Scene &scene) override;
        virtual void update(const Scene& scene, std::uint32_t dt) override;
        virtual void render(const Scene &scene, SDL_Renderer *renderer) override;
        virtual void destroy() override;
        virtual void on_notify(Event &e) override;

        int get_sprite_index(const std::size_t row, const std::size_t col);

        bool is_empty(const std::size_t row, const std::size_t col);

    public:
        bool toggled = true;
		std::size_t w, h;
        std::string sprite_sheet_path;
        std::unique_ptr<SpriteSheet> wall_sprites;
        std::vector<char> map_data;

        // TODO
        // std::vector<std::uint8_t> properties;
        // std::vector<std::uint32_t> sprites;
    };
}

#endif