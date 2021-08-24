#ifndef ZJVL_SCENE_MAP_H
#define ZJVL_SCENE_MAP_H

#include "all.h"
#include <SDL2/SDL.h>
#include "asset/assets/sprite_sheet.h"
#include "asset/assets/texture.h"
#include "scene/game_object.h"
#include "event/event.h"
#include "core/vec2.h"

namespace ZJVL
{
    class Map : public GameObject
    {
    public:
        Map(std::string name, Vec2 vec2, std::size_t w, std::size_t h, std::string sprite_sheet);

        bool create() override;
        virtual void update(std::uint32_t dt) override;
        virtual void render(SDL_Renderer *renderer) override;
        void destroy() override;
        void on_notify(Event &e) override;

        int get_sprite_index(const std::size_t row, const std::size_t col);

        bool is_empty(const std::size_t row, const std::size_t col);

    public:
        // TODO: For now, size of map, default is 16 for each
        std::string name;
        std::string sprite_sheet_path;
        std::unique_ptr<SpriteSheet> wall_sprites;
        std::unique_ptr<Texture> texture;

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

        bool show = true;
    };
}

#endif