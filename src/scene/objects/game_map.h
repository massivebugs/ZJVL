#ifndef ZJVL_SCENE_GAMEMAP_H
#define ZJVL_SCENE_GAMEMAP_H

#include "all.h"
#include <SDL2/SDL.h>
#include "core/vec2.h"
#include "scene/game_object.h"
#include "scene/scene.h"
#include "event/event.h"
#include "asset/assets/sprite_sheet.h"
#include "asset/assets/texture.h"

namespace ZJVL
{
    class GameMap : public GameObject
    {
    public:
        GameMap(std::string sprite_sheet);

        virtual bool create(const Scene& scene) override;
        virtual void update(std::uint32_t dt) override;
        virtual void render(SDL_Renderer *renderer) override;
        virtual void destroy() override;
        virtual void on_notify(Event &e) override;

        int get_sprite_index(const std::size_t row, const std::size_t col);

        bool is_empty(const std::size_t row, const std::size_t col);

    public:
        std::string sprite_sheet_path;
        std::unique_ptr<SpriteSheet> wall_sprites;
        std::unique_ptr<Texture> texture;

        // TODO
        std::vector<std::uint8_t> properties;
        std::vector<std::uint32_t> sprites;

        bool toggled = true;

        const char map[16 * 16 + 1] = "0000222222220000"
                                      "1              0"
                                      "1      11111   0"
                                      "1     4        0"
                                      "0     0  1114444"
                                      "5     3        0"
                                      "5   30000      0"
                                      "5   0   11100  0"
                                      "5   0   0      0"
                                      "5   0   1  00000"
                                      "5       1      0"
                                      "2       1      0"
                                      "0       0      0"
                                      "0 0000000      0"
                                      "0              0"
                                      "0002222222200000";
        std::size_t x_tiles = 16, y_tiles = 16;
    };
}

#endif