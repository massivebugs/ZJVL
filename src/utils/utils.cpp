#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cassert>

#include "utils.h"
#include "scene/entity.h"

namespace ZJVL
{
	// Return a 32 byte unsigned int containing rgba values
	uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
	{
		return (a << 24) + (b << 16) + (g << 8) + r;
	}

	// // Retrieve rgba values from a 32 byte unsigned int
	// void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a)
	// {
	// 	// Shift away unnecessary bits (since rgba is 255 bits * 4)
	// 	// and pluck out least significant 8 bits
	// 	r = (color >> 0) & 255;
	// 	g = (color >> 8) & 255;
	// 	b = (color >> 16) & 255;
	// 	a = (color >> 24) & 255;
	// }
}