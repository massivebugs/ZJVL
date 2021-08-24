#include "all.h"
#include "map.h"
#include "scene/game_object.h"
#include "asset/assets/sprite_sheet.h"
#include "event/event.h"
#include "core/vec2.h"

namespace ZJVL
{
    Map::Map(std::string name, Vec2 vec2, std::size_t w, std::size_t h, std::string sprite_sheet)
        : GameObject(vec2, w, h),
          name(name),
          sprite_sheet_path(sprite_sheet){};

    bool Map::create()
    {
        assert(sizeof(map) == x_tiles * y_tiles + 1); // + 1 for null terminated string
        wall_sprites = std::make_unique<SpriteSheet>(sprite_sheet_path);

        if (wall_sprites->buffer.empty())
        {
            return false;
        }

        texture = std::make_unique<Texture>(x_tiles, y_tiles);

        return true;
    };

    void Map::update(std::uint32_t dt){};

    void Map::render(SDL_Renderer *renderer)
    {
        // std::size_t rect_w = w / x_tiles;
        // std::size_t rect_h = h / y_tiles;

        // for (std::size_t row = 0; row < y_tiles; row++)
        // {
        //     for (std::size_t col = 0; col < x_tiles; col++)
        //     {
        //         // Do nothing with empty spaces on the map
        //         if (is_empty(row, col))
        //             continue;

        //         // position of the part we are drawing
        //         // so it would draw rect_w * rect_h size rectangle on position i * j of the map
        //         std::size_t rect_y = row * rect_h;
        //         std::size_t rect_x = col * rect_w;

        //         std::size_t texture_index = get_sprite_index(row, col);
        //         assert(texture_index < wall_sprites->count);

        //         // Upper left pixel color
        //         draw_rectangle(rect_x, rect_y, rect_w, rect_h, wall_sprites->get(0, 0, texture_index));
        //     }
        // }
    };

    void Map::destroy()
    {
        wall_sprites.reset();
        texture.reset();
    };

    void Map::on_notify(Event &e)
    {
        // Show like a pin on a map or smth
    }

    int Map::get_sprite_index(const std::size_t row, const std::size_t col)
    {
        assert(row < y_tiles && col < x_tiles && sizeof(map) == x_tiles * y_tiles + 1);
        return map[col + row * x_tiles] - '0';
    }

    bool Map::is_empty(const std::size_t row, const std::size_t col)
    {
        assert(row < h && col < x_tiles && sizeof(map) == x_tiles * y_tiles + 1);
        return map[col + row * x_tiles] == ' ';
    }
}