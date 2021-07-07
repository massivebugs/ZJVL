#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cassert>
#include <cmath>

#include "utils.h"
#include "entity/entity.h"

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

void merge(std::vector<Entity> &l_vect, std::vector<Entity> &r_vect, std::vector<Entity> &merged)
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

void sort_entities(std::vector<Entity> &to_sort)
{
	// Merge sort entities just for practice
	if (to_sort.size() == 1)
		return;

	std::size_t half_idx = std::ceil((float)to_sort.size() / 2);

	// The iterator pointing to the half element of the vector
	std::vector<Entity>::iterator half_iter = to_sort.end() - (to_sort.size() - half_idx);

	// Iterators in C++ by The Cherno https://www.youtube.com/watch?v=SgcHcbQ0RCQ
	std::vector<Entity> l_half(to_sort.begin(), half_iter);
	std::vector<Entity> r_half(half_iter, to_sort.end());

	sort_entities(l_half);
	sort_entities(r_half);

	merge(l_half, r_half, to_sort);
}