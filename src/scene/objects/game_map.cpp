#include "all.h"
#include "game_map.h"
#include "scene/game_object.h"
#include "scene/scene.h"
#include "asset/sprite_sheet.h"
#include "event/event.h"
#include "core/vec2.h"

namespace ZJVL
{
    GameMap::GameMap(std::string sprite_sheet)
        : sprite_sheet_path(sprite_sheet){};

    bool GameMap::create(const Scene &scene)
    {
        assert(map_data.size() == w * h); // + 1 for null terminated string
        wall_sprites = std::make_unique<SpriteSheet>(sprite_sheet_path);
        return !wall_sprites->buffer.empty();
    };

    void GameMap::update(const Scene &scene, std::uint32_t dt){
        // std::cout << "On Map Update: " << scene->texture.w << std::endl;
    };

    void GameMap::render(const Scene &scene, SDL_Renderer *renderer)
    {
        // Size of blocks on the map (wall, etc)
        std::size_t rect_w = (scene.texture.w / 2) / w;
        std::size_t rect_h = scene.texture.h / h;

        for (std::size_t row = 0; row < h; row++)
        {
            for (std::size_t col = 0; col < w; col++)
            {
                // Do nothing with empty spaces on the map
                if (is_empty(row, col))
                    continue;

                // position of the part we are drawing
                // so it would draw rect_w * rect_h size rectangle on position i * j of the map
                std::size_t rect_y = row * rect_h;
                std::size_t rect_x = col * rect_w;

                std::size_t texture_index = get_sprite_index(row, col);
                assert(texture_index < wall_sprites->count);

                // TODO: Render directly to texture
                // TODO: Set player location
                // TODO: Set actors location
            }
        }
    };

    void GameMap::destroy()
    {
        wall_sprites.reset();
    };

    void GameMap::on_notify(Event &e)
    {
        // Show like a pin on a map or smth
    }

    int GameMap::get_sprite_index(const std::size_t row, const std::size_t col)
    {
        assert(row < h && col < w);
        return map_data[col + row * w] - '0';
    }

    bool GameMap::is_empty(const std::size_t row, const std::size_t col)
    {
        assert(row < h && col < w);
        return map_data[col + row * w] == ' ';
    }
}