#ifndef ZJVL_CORE_SPRITESHEET_H
#define ZJVL_CORE_SPRITESHEET_H

#include "all.h"
#include "asset.h"
#include "image.h"

namespace ZJVL
{
	namespace Asset
	{
		class SpriteSheet : public Asset
		{
		public:
			SpriteSheet(std::string path) : image(path)
			{
				// Individual tiles are squares for now
				count = image.w / image.h;

				// The size of each tile
				size = image.w / count;
			}

			~SpriteSheet()
			{
			}

			std::vector<uint32_t> get_scaled_column(const std::size_t index, const std::size_t col, const std::size_t column_height)
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

			std::uint32_t &get(const std::size_t row, const std::size_t col, const std::size_t index)
			{
				assert(row < size && col < size && index < count);
				return image.data[col + (index * size) + (row * image.w)];
			}

			Image image;
			std::size_t count;
			std::size_t size;
		};
	}
}

#endif