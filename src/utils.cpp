#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cassert>
#include <cmath>

#include "utils.h"
#include "sprite.h"

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

bool is_transparent_pixel(const uint32_t &color)
{
	std::uint8_t opacity = color >> 24 & 255;
	return opacity == 0;
}

void merge(std::vector<Sprite> &l_vect, std::vector<Sprite> &r_vect, std::vector<Sprite> &merged)
{
	std::size_t merged_idx = 0;
	std::size_t l_size = l_vect.size();
	std::size_t r_size = r_vect.size();
	std::size_t l_idx = 0;
	std::size_t r_idx = 0;

	for (merged_idx; merged_idx < merged.size(); merged_idx++)
	{
		if (l_idx == l_size)
		{
			merged[merged_idx] = r_vect[r_idx];
			r_idx++;
			continue;
		}
		else if (r_idx == r_size)
		{
			merged[merged_idx] = l_vect[l_idx];
			l_idx++;
			continue;
		}

		// compare and add the smaller size to merged
		if (l_vect[l_idx] < r_vect[r_idx])
		{
			merged[merged_idx] = l_vect[l_idx];
			l_idx++;
		}
		else
		{
			merged[merged_idx] = r_vect[r_idx];
			r_idx++;
		}
	}
}

void sort_sprites(std::vector<Sprite> &to_sort)
{
	// Merge sort sprites just for practice
	if (to_sort.size() == 1)
		return;

	std::size_t half_idx = std::ceil((float)to_sort.size() / 2);

	// The iterator pointing to the half element of the vector
	std::vector<Sprite>::iterator half_iter = to_sort.end() - (to_sort.size() - half_idx);

	// Iterators in C++ by The Cherno https://www.youtube.com/watch?v=SgcHcbQ0RCQ
	std::vector<Sprite> l_half(to_sort.begin(), half_iter);
	std::vector<Sprite> r_half(half_iter, to_sort.end());

	sort_sprites(l_half);
	sort_sprites(r_half);

	merge(l_half, r_half, to_sort);
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
