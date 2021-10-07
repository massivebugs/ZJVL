#include "all.h"
#include <SDL2/SDL.h>
#include "game_map.h"
#include "scene/scene.h"
#include "event/event.h"
#include "event/key_event.h"
#include "asset/sprite_sheet.h"
#include "util/vec2.h"

namespace ZJVL
{
    GameMap::GameMap(std::string sprite_sheet)
        : m_sprite_sheet_path(sprite_sheet), w(100), h(100){};

    bool GameMap::create(const Scene &scene)
    {
        assert(map_data.size() == x_tiles_count * y_tiles_count); // + 1 for null terminated string

        m_tile_w = w / x_tiles_count;
        m_tile_h = h / y_tiles_count;

        m_wall_sprites = std::make_unique<SpriteSheet>(m_sprite_sheet_path);
        return !m_wall_sprites->buffer.empty();
    };

    void GameMap::update(const Scene &scene, std::uint32_t dt){};

    void GameMap::render(const Scene &scene, SDL_Renderer *renderer)
    {
        // No need to render if it's not toggled
        if (!toggled)
            return;

        for (int row = 0; row < y_tiles_count; row++)
        {
            for (int col = 0; col < x_tiles_count; col++)
            {
                // Do nothing with empty spaces on the map
                if (is_empty(row, col))
                    continue;

                // std::size_t texture_index = get_sprite_index(row, col);
                // assert(texture_index < m_wall_sprites->count);

                // Draw rect_w * rect_h size rectangle on position i * j of the map
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_Rect map_wall = {(int)pos.x + col * m_tile_w, (int)pos.y + row * m_tile_h, m_tile_w, m_tile_h};
                SDL_RenderDrawRect(renderer, &map_wall);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        for (auto object : scene.objects)
        {
            SDL_Rect object_loc = {(int)pos.x + (int)object->pos.x, (int)pos.y + (int)object->pos.y, 5, 5};
            SDL_RenderFillRect(renderer, &object_loc);
            // TODO: Render a positional icon
        }
    };

    void GameMap::destroy()
    {
        m_wall_sprites.reset();
    };

    void GameMap::on_notify(Event &e)
    {
        switch (e.get_type())
        {
        case EventType::KEYDOWN:
            switch (static_cast<KeyDownEvent &>(e).get_key())
            {
            case Key::M:
                toggled = !toggled;
                break;
            }
            break;
        }
    }

    int GameMap::get_sprite_index(const std::size_t row, const std::size_t col)
    {
        assert(row < y_tiles_count && col < x_tiles_count);
        return map_data[col + row * x_tiles_count] - '0';
    }

    bool GameMap::is_empty(const std::size_t row, const std::size_t col)
    {
        assert(row < y_tiles_count && col < x_tiles_count);
        return map_data[col + row * x_tiles_count] == ' ';
    }
}