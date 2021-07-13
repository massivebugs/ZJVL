
#ifndef ZJVL_UTILS_H
#define ZJVL_UTILS_H

#include <vector>
#include <cstdint>
#include <string>

namespace Engine
{
	uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);
	// void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a);
}

#endif