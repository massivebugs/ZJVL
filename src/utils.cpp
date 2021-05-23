#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cassert>

#include "utils.h"

// Return a 32 byte unsigned int containing rgba values
uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
	return (a << 24) + (b << 16) + (g << 8) + r;
}

// Retrieve rgba values from a 32 byte unsigned int
void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a)
{
	// Shift away unnecessary bits (since rgba is 255 bits * 4)
	// and pluck out least significant 8 bits
	r = (color >> 0) & 255;
	g = (color >> 8) & 255;
	b = (color >> 16) & 255;
	a = (color >> 24) & 255;
}

// Outputs a vector(array of rgba values) into a file
void drop_ppm_image(const std::string filename, const std::vector<uint32_t> &image, const size_t w, const size_t h)
{
	// vector::size returns the number of elements in the vector.
	// Thus, w * h would simply return all the number of pixels in an image
	assert(image.size() == w * h);

	// Open a binary output file stream (shorthand expr for ofs.open)
	std::ofstream ofs(filename, std::ios::binary);

	// PPM syntax
	ofs << "P6\n"
		<< w << " " << h << "\n255\n";

	const int all_pix = h * w;
	for (size_t curr_pix = 0; curr_pix < all_pix; curr_pix++)
	{
		uint8_t r, g, b, a;

		unpack_color(image[curr_pix], r, g, b, a);

		// Use static casts if you are sure about the validity of the cast,
		// in which <uint8_t> here is definitely 1 byte,
		// so we are converting it to a type of the same memory size <char> which is also 1 byte.
		// Do we actually need static cast here? Cant we just do char r,g,b,a;?
		ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
	}

	// Not strictly necessary
	ofs.close();
}
