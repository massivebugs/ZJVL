#include "all.h"
#include "sprite_sheet.h"
#include "image.h"

namespace ZJVL
{
    SpriteSheet::SpriteSheet(std::string path) : Image(path)
    {
        // Individual tiles are squares for now
        count = w / h;

        // The size of each tile
        size = w / count;
    }

    std::vector<uint32_t> SpriteSheet::get_scaled_column(const std::size_t index, const std::size_t col, const std::size_t column_height)
    {
        assert(col < size && index < count);
        std::vector<std::uint32_t> column(column_height);

        for (int curr_column_height = 0; curr_column_height < column_height; curr_column_height++)
        {
            std::size_t row = float(size) / float(column_height) * curr_column_height;
            column[curr_column_height] = get(row, col, index);
        }

        return column;
    }

    std::uint32_t &SpriteSheet::get(const std::size_t row, const std::size_t col, const std::size_t index)
    {
        assert(row < size && col < size && index < count);
        return buffer[col + (index * size) + (row * w)];
    }
}