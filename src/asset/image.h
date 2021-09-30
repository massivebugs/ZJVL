#ifndef ZJVL_ASSET_IMAGE_H
#define ZJVL_ASSET_IMAGE_H

#include "all.h"
#include "asset.h"

namespace ZJVL
{
	class Image : public Asset
	{
	public:
		Image(std::string path);

		virtual ~Image() = default;

		std::vector<std::uint32_t> buffer;
		std::size_t w, h;
	};
}

#endif