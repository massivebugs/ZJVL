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
#include "utils.h"
#include "textures.h"
#include "framebuffer.h"
#include "map.h"
#include "player.h"

void render(FrameBuffer &framebuffer, Map &map, Player &player, Texture &wall_tex)
{

	framebuffer.clear(pack_color(255, 255, 255));

	// Blocks on the map (wall, etc)
	const std::size_t rect_w = (framebuffer.w / 2) / map.w;
	const std::size_t rect_h = framebuffer.h / map.h;

	// Render the map
	for (std::size_t row = 0; row < map.h; row++)
	{
		for (std::size_t col = 0; col < map.w; col++)
		{
			// Do nothing with empty spaces on the map
			if (map.is_empty(row, col))
				continue;

			// position of the part we are drawing
			// so it would draw rect_w * rect_h size rectangle on position i * j of the map
			std::size_t rect_y = row * rect_h;
			std::size_t rect_x = col * rect_w;

			std::size_t texture_index = map.get(row, col);
			assert(texture_index < wall_tex.count);

			// The color is taken from the upper left pixel of the texture for the map
			framebuffer.draw_rectangle(rect_x, rect_y, rect_w, rect_h, wall_tex.get(0, 0, texture_index));
		}
	}

	// Show player position on the map
	framebuffer.draw_rectangle(player.x * rect_w, player.y * rect_h, 5, 5, pack_color(0, 255, 0));

	// window_w so we can see through the whole screen
	for (std::size_t i = 0; i < framebuffer.w / 2; i++)
	{
		// fov * i / float(window_w / 2) increasingly gives higher value until it reaches 100% of fov, so that we can actually rotate the ray
		// player_angle is the current viewing point, directly ahead. fov / 2 is setting the current view to render to be the left peripheral
		float angle = player.a - player.fov / 2 + player.fov * i / float(framebuffer.w / 2);

		// soh cah toa
		// hypothenuse = h, adjacent = a, opposite = o
		// by setting an arbitrary hypotheneuse length, we can calculate the length of a && o using trig functions
		// https://www.quora.com/What-is-the-purpose-of-the-sin-cos-and-tan-functions
		// hypothenuse h, and the rate we are extending it h_step
		const float h_step = 0.01;
		for (float h = 0; h < 20; h += h_step)
		{
			// offset_x + h * a / h so we just get a!
			float view_x = player.x + h * cos(angle);
			float view_y = player.y + h * sin(angle);

			std::size_t pix_x = view_x * rect_w;
			std::size_t pix_y = view_y * rect_h;

			// This draws the visibility cone
			framebuffer.set_pixel(pix_x, pix_y, pack_color(160, 160, 160));

			// ray is touching a wall
			if (map.is_empty(view_y, view_x) == false)
			{
				// http://www.permadi.com/tutorial/raycast/rayc4.html
				size_t wall_height = framebuffer.h / (h * cos(angle - player.a));
				size_t texture_index = map.get(view_y, view_x);

				// Count texture pixels
				float hit;
				// Check if the position we are at is almost a whole number (6.01 etc due to hypotheneuse length offset)
				float offset = view_x - (int)view_x;
				if (offset < 1 - h_step && offset > h_step)
				{
					// We hit a wall on the x plane!
					hit = view_x - (int)view_x; // because view_x represents how many blocks
				}
				else
				{
					// We hit a wall on the y plane!
					hit = view_y - (int)view_y;
				}
				// The current column of the texture we need to extract pixels from
				int texture_col = wall_tex.size * hit;

				assert(texture_col < wall_tex.size);

				std::vector<uint32_t> column = wall_tex.get_scaled_column(texture_index, texture_col, wall_height);

				for (int curr_height = 0; curr_height < column.size(); curr_height++)
				{
					framebuffer.set_pixel(framebuffer.w / 2 + i, (framebuffer.h / 2) - (wall_height / 2) + curr_height, column[curr_height]);
				}
				break;
			}
		}
	}
}

int main(int argc, char *argv[])
{

	// Set size of framebuffer
	FrameBuffer framebuffer{1024, 512};
	// Clear and reset framebuffer image to white
	framebuffer.clear(pack_color(255, 255, 255));

	// player position x, y, initial player view direction (angle between view direction and x axis), fov (1/3rd of screen)
	Player player{3.456, 2.345, 1.523, M_PI / 3.};

	Map map;

	Texture wall_tex("assets/walltext.png");

	if (wall_tex.count == 0)
	{
		std::cerr << "Failed to load wall textures" << std::endl;
		return -1;
	}

	for (size_t frame_num = 0; frame_num < 360; frame_num++)
	{
		std::stringstream ss;

		// Set the name of the output frame (ppm) file
		// Fill 5 0's as initial string and then add the frame number
		ss << std::setfill('0') << std::setw(5) << frame_num << ".ppm";

		player.a += 2 * (M_PI / 360);

		render(framebuffer, map, player, wall_tex);
		drop_ppm_image(ss.str(), framebuffer.img, framebuffer.w, framebuffer.h);
	}
}