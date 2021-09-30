#ifndef ZJVL_ASSET_SPRITESHEET_H
#define ZJVL_ASSET_SPRITESHEET_H

#include "all.h"
#include "asset.h"
#include "image.h"

namespace ZJVL
{
	class SpriteSheet : public Image
	{
	public:
		SpriteSheet(std::string path);

		~SpriteSheet() = default;

		std::vector<uint32_t> get_scaled_column(const std::size_t index, const std::size_t col, const std::size_t column_height);

		std::uint32_t &get(const std::size_t row, const std::size_t col, const std::size_t index);

		std::size_t count;
		std::size_t size;
	};
}

#endif