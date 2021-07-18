#ifndef ZJVL_FRAMEWORK_UTILS_H
#define ZJVL_FRAMEWORK_UTILS_H
#include <cstdint>
#include <vector>

namespace ZJVL
{
	namespace Framework
	{
		class Utils
		{
		public:
			static void load_image(const char *path, std::vector<std::uint32_t> *img, std::size_t *img_w, std::size_t *img_h);
		};
	}
}

#endif