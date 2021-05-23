// Library references
// - cstdint: https://stackoverflow.com/questions/6144682/should-i-use-cstdint
// - stb_image.h: https://github.com/nothings/stb

// New things I have learned
// * const in C++ by Cherno: https://www.youtube.com/watch?v=4fJBrditnJU
// * uint8_t: unsigned integer type with width of exactly 8 bits (1 byte, 0 to 255) kinda good for colors
// * std::size_t: std::size_t is result of sizeof. Use size_t for variables that model size or index in an array.
// * std::ofstream output file stream. There is also ifstream!
//   the second argument for file.open() are modes like std::ios::app for append
//   http://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-2.html
// * PPM files: http://netpbm.sourceforge.net/doc/ppm.html
// * static_cast: Casting in C++ by Cherno - https://www.youtube.com/watch?v=pWZS1MtxI-A
// http://www.cplusplus.com/doc/tutorial/typecasting/
// * float division: returns float if divided by float! std::cout << 255 * (2 / float(3)) << std::endl;
// * NULL, null_ptr: https://stackoverflow.com/questions/20509734/null-vs-nullptr-why-was-it-replaced

#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
#include <math.h>
#include <sstream>
#include <iomanip>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "utils.h"

bool load_textures(const char *filename, std::vector<uint32_t> &textures, int &texture_x_pix, int &texture_y_pix, int &textures_count, int &texture_w)
{
	int texture_pix_channels;
	const int texture_pix_length = 4; // RGBA

	unsigned char *texture_data = stbi_load(filename, &texture_x_pix, &texture_y_pix, &texture_pix_channels, texture_pix_length);
	assert(texture_data != NULL);

	textures = std::vector<uint32_t>(texture_y_pix * texture_x_pix);
	// Load the texture into stack memory and close file
	for (int j = 0; j < texture_y_pix; j++)
	{
		for (int i = 0; i < texture_x_pix; i++)
		{
			uint32_t texture_pixel = pack_color(
				texture_data[(i + j * texture_x_pix) * 4],
				texture_data[(i + j * texture_x_pix) * 4 + 1],
				texture_data[(i + j * texture_x_pix) * 4 + 2],
				texture_data[(i + j * texture_x_pix) * 4 + 3]);

			textures[i + j * texture_x_pix] = texture_pixel;
		}
	}

	// Textures are squares
	textures_count = texture_x_pix / texture_y_pix;

	// Get width of each texture tile
	texture_w = texture_x_pix / textures_count;

	stbi_image_free(texture_data);
	return true;
}

// Places a single color rectangle (arbitrary of size) onto a image (<vector>)
void draw_rectangle(std::vector<uint32_t> &img, const size_t img_w, const size_t img_h, const size_t rect_x, const size_t rect_y, const size_t rect_w, const size_t rect_h, const uint32_t color)
{
	assert(img.size() == img_w * img_h);

	// for the size of the rectangle we are about to draw, draw the color
	for (size_t offset_h = 0; offset_h < rect_h; offset_h++)
	{
		for (size_t offset_w = 0; offset_w < rect_w; offset_w++)
		{
			size_t x = rect_x + offset_w;
			size_t y = rect_y + offset_h;

			// Skip any overflows
			if (x >= img_w || y >= img_h)
				continue;

			img[x + y * img_w] = color;
		}
	}
}

int main(int argc, char *argv[])
{
	const size_t window_w = 1024;
	const size_t window_h = 512;

	// the image itself, initialized to red
	// vector initialization
	// Create a vector of size window_w * window_h with all values as 255.
	std::vector<uint32_t> framebuffer(window_w * window_h, pack_color(255, 255, 255));

	// A game map containing 16 * 16 blocks
	const size_t map_x_blocks = 16;
	const size_t map_y_blocks = 16;
	const char map[] = "0000222222220000"
					   "1              0"
					   "1      11111   0"
					   "1     4        0"
					   "0     0  1114444"
					   "5     3        0"
					   "5   30000      0"
					   "5   0   11100  0"
					   "5   0   0      0"
					   "5   0   1  00000"
					   "5       1      0"
					   "2       1      0"
					   "0       0      0"
					   "0 0000000      0"
					   "0              0"
					   "0002222222200000";

	assert(sizeof(map) == map_x_blocks * map_y_blocks + 1); // +1 for the null terminated string

	// These are just pixel values!
	float player_x = 3.456;
	float player_y = 2.345;

	// Initial player view direction (angle) - angle between view direction and x axis
	float player_angle = 1.523;

	// field of view, 1/3rd
	float fov = M_PI / 3.;

	// Blocks on the map (wall, etc)
	const size_t block_w = (window_w / 2) / map_x_blocks;
	const size_t block_h = window_h / map_y_blocks;

	// Textures
	int texture_x_pix, texture_y_pix, textures_count, texture_w;
	std::vector<uint32_t> wall_textures;
	const bool texture_load_result = load_textures("assets/walltext.png", wall_textures, texture_x_pix, texture_y_pix, textures_count, texture_w);
	if (texture_load_result == false)
	{
		std::cout << "Failed to load textures\n";
		return -1;
	}

	// for (size_t frame_num = 0; frame_num < 360; frame_num++)
	// {
	// 	std::stringstream ss;

	// 	// Set the name of the output frame (ppm) file
	// 	// Fill 5 0's as initial string and then add the frame number
	// 	ss << std::setfill('0') << std::setw(5) << frame_num << ".ppm";

	// 	player_angle += 2 * (M_PI / 360);

	// 	// Clear the framebuffer
	// 	framebuffer = std::vector<uint32_t>(window_w * window_h, pack_color(255, 255, 255));

	// Render the map
	for (size_t j = 0; j < map_y_blocks; j++)
	{
		for (size_t i = 0; i < map_x_blocks; i++)
		{
			// Do nothing with empty spaces on the map
			if (map[i + j * map_x_blocks] == ' ')
				continue;

			// position of the part we are drawing
			// so it would draw block_w * block_h size rectangle on position i * j of the map
			size_t rect_x = i * block_w;
			size_t rect_y = j * block_h;

			// https://stackoverflow.com/questions/15598698/why-does-subtracting-0-in-c-result-in-the-number-that-the-char-is-representing
			// https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
			// This is kinda like char to int conversion. '0' is 48 and '9' is 57. 57 - 48 is 9. So it's kinda like '9' - 48
			size_t texture_index = map[i + j * map_x_blocks] - '0';

			draw_rectangle(framebuffer, window_w, window_h, rect_x, rect_y, block_w, block_h, wall_textures[texture_index * texture_w]);
		}
	}

	// Show player position on the map
	// draw_rectangle(framebuffer, window_w, window_h, player_x * block_w, player_y * block_h, 5, 5, pack_color(255, 255, 255));

	// soh cah toa
	// hypothenuse = h, adjacent = a, opposite = o
	// by setting an arbitrary hypotheneuse length, we can calculate the length of a && o using trig functions
	// https://www.quora.com/What-is-the-purpose-of-the-sin-cos-and-tan-functions
	// window_w so we can see through the whole screen
	for (size_t i = 0; i < window_w / 2; i++)
	{
		// fov * i / float(window_w / 2) increasingly gives higher value until it reaches 100% of fov, so that we can actually rotate the ray
		// player_angle is the current viewing point, directly ahead. fov / 2 is setting the current view to render to be the left peripheral
		float angle = player_angle - fov / 2 + fov * i / float(window_w / 2);
		float h = 0;
		float height = 0;

		// hypothenuse
		const float h_step = 0.01;
		for (; h < 20; h += h_step)
		{
			float vx = player_x + h * cos(angle); // offset_x + h * a / h so we just get a!
			float vy = player_y + h * sin(angle);

			size_t pix_x = vx * block_w;
			size_t pix_y = vy * block_h;

			// This draws the visibility cone
			framebuffer[pix_x + pix_y * window_w] = pack_color(160, 160, 160);

			// ray is touching a wall
			if (map[int(vx) + int(vy) * map_x_blocks] != ' ')
			{
				// http://www.permadi.com/tutorial/raycast/rayc4.html
				size_t wall_height = window_h / (h * cos(angle - player_angle));
				size_t texture_index = map[int(vx) + int(vy) * map_x_blocks] - '0';

				// Count texture pixels
				float hit;
				// Check if the position we are at is almost a whole number (6.01 etc due to hypotheneuse length offset)
				float offset = vx - (int)vx;
				if (offset < 1 - h_step && offset > h_step)
				{
					// We hit a wall on the x plane!
					hit = vx - (int)vx; // because vx represents how many blocks
				}
				else
				{
					// We hit a wall on the y plane!
					hit = vy - (int)vy;
				}
				// The current column of the texture we need to extract pixels from
				int texture_col = texture_w * hit;

				assert(texture_col <= texture_w);

				// Loop over from top to bottom, and stretch or shorten the texture to fit the wall height
				for (int curr_wall_height = 0; curr_wall_height < wall_height; curr_wall_height++)
				{
					int texture_row = float(texture_y_pix) / float(wall_height) * curr_wall_height;
					// Get the pixel by 1. skipping to index, adding column and adding to initial row position
					draw_rectangle(framebuffer, window_w, window_h, window_w / 2 + i, (window_h / 2) - (wall_height / 2) + curr_wall_height, 1, 1, wall_textures[(texture_index * texture_w) + texture_col + (texture_row * texture_x_pix)]);
				}

				break;
			}
		}
	}
	drop_ppm_image("./out.ppm", framebuffer, window_w, window_h);
	// drop_ppm_image(ss.str(), framebuffer, window_w, window_h);
	// }
}