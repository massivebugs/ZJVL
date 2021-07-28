#include "all.h"
#include "textures.h"
#include "framework/utils.h"

namespace ZJVL
{
    namespace Core
    {
        Texture::Texture(const char *path) : img_w(0), img_h(0), count(0), size(0), img()
        {
            img_w = 0;
            img_h = 0;

            Framework::Utils::load_image(path, &img, &img_w, &img_h);

            // Textures are squares
            count = img_w / img_h;

            // Get width of each texture tile
            size = img_w / count;
        }

        std::uint32_t &Texture::get(const std::size_t row, const std::size_t col, const std::size_t index)
        {
            assert(row < size && col < size && index < count);
            return img[col + (index * size) + (row * img_w)];
        }

        std::vector<uint32_t> Texture::get_scaled_column(const std::size_t index, const std::size_t col, const std::size_t column_height)
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

    }
}