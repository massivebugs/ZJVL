#include <cstdint>

class Utils
{
public:
	uint8_t *load_image(const char *path, int *img_w, int *img_h);
};