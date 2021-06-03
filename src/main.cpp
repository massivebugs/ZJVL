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
#include "sprite.h"

void draw_map(FrameBuffer &framebuffer, Map &map, std::size_t rect_w, std::size_t rect_h, Texture &wall_tex)
{
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
}

void draw_sprite(FrameBuffer &framebuffer, Player &player, Sprite &sprite, Texture &sprite_tex, std::vector<float> &depth_buffer)
{
	// https://www.youtube.com/watch?v=BJ0-3kERCwc
	// https://www.youtube.com/watch?v=MHoFqRyeP3o の2:52を見てみるとちょっとわかるかも
	// https://boxbase.org/entries/2014/jun/23/why-radians/ Why we use radians
	// sprite_dir is like the angle between the x axis and curr sprite's location
	float sprite_dir = atan2(sprite.y - player.y, sprite.x - player.x);

	// TODO: Wtf is this?!
	while (sprite_dir - player.a > M_PI) // while sprite in the oppsite+ direction
		sprite_dir -= 2 * M_PI;			 // remove unncesessary periods from the relative direction
	while (sprite_dir - player.a < -M_PI)
		sprite_dir += 2 * M_PI;

	size_t sprite_size = std::min(1000, static_cast<int>(framebuffer.h / sprite.player_dist));

	// Kind of like when drawing the wall. Gets the upper left coordinates of the sprite to draw
	int w_offset = (sprite_dir - player.a) * (framebuffer.w / 2) / (player.fov) + (framebuffer.w / 2) / 2 - sprite_size / 2;
	int h_offset = (framebuffer.h / 2) - (sprite_size / 2);

	for (size_t i = 0; i < sprite_size; i++)
	{
		if (w_offset + int(i) < 0 || w_offset + i >= framebuffer.w / 2)
			continue;

		// Don't draw the sprite if it is behind a wall
		if (depth_buffer[w_offset + i] <= sprite.player_dist)
			continue;

		size_t sprite_col = (float(sprite_tex.size) / float(sprite_size)) * i;

		std::vector<uint32_t> column = sprite_tex.get_scaled_column(sprite.texture_index, sprite_col, sprite_size);
		for (int curr_height = 0; curr_height < column.size(); curr_height++)
		{
			if (is_transparent_pixel(column[curr_height]))
				continue;

			framebuffer.set_pixel(framebuffer.w / 2 + w_offset + i, (framebuffer.h / 2) - (sprite_size / 2) + curr_height, column[curr_height]);
		}
	}
}

void cast_ray(FrameBuffer &framebuffer, Map &map, std::size_t rect_w, std::size_t rect_h, Player &player, Texture &wall_tex, std::vector<float> &depth_buffer)
{
	// window_w so we can render the whole screen width
	for (std::size_t i = 0; i < framebuffer.w / 2; i++)
	{
		// fov * i / float(window_w / 2) increasingly gives higher value until it reaches 100% of fov, so that we can actually rotate the ray
		// curr_angle is the current viewing point, directly ahead. fov / 2 is setting the current view to render to be the left peripheral
		float curr_angle = player.a - player.fov / 2 + player.fov * i / float(framebuffer.w / 2);

		// soh cah toa
		// hypothenuse = h, adjacent = a, opposite = o
		// by setting an arbitrary hypotheneuse length, we can calculate the length of a && o using trig functions
		// https://www.quora.com/What-is-the-purpose-of-the-sin-cos-and-tan-functions
		// hypothenuse h, and the rate we are extending it h_step
		const float h_step = 0.01;
		for (float h = 0; h < 20; h += h_step)
		{
			// offset_x + h * a / h so we just get a!
			float view_x = player.x + h * cos(curr_angle);
			float view_y = player.y + h * sin(curr_angle);

			std::size_t pix_x = view_x * rect_w;
			std::size_t pix_y = view_y * rect_h;

			// This draws the visibility cone
			framebuffer.set_pixel(pix_x, pix_y, pack_color(160, 160, 160));
			// std::cout << view_x << ':' << view_y << std::endl;

			// ray is touching a wall
			if (map.is_empty(view_y, view_x) == false)
			{
				// Store the depth of the map
				depth_buffer[i] = h;

				// http://www.permadi.com/tutorial/raycast/rayc4.html
				size_t wall_height = framebuffer.h / (h * cos(curr_angle - player.a));
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

void render(FrameBuffer &framebuffer, Map &map, Player &player, std::vector<Sprite> &sprites, Texture &wall_tex, Texture &sprites_tex)
{

	// Clear and reset framebuffer image to white
	framebuffer.clear(pack_color(255, 255, 255));

	// Size of blocks on the map (wall, etc)
	const std::size_t rect_w = (framebuffer.w / 2) / map.w;
	const std::size_t rect_h = framebuffer.h / map.h;

	// Depth map of the walls
	std::vector<float> depth_buffer(framebuffer.w / 2, 1e3);

	draw_map(framebuffer, map, rect_w, rect_h, wall_tex);

	cast_ray(framebuffer, map, rect_w, rect_h, player, wall_tex, depth_buffer);

	// Show player position on the map
	framebuffer.draw_rectangle(player.x * rect_w, player.y * rect_h, 5, 5, pack_color(0, 255, 0));

	// Store sprite distance relative to player
	for (int i = 0; i < sprites.size(); i++)
	{
		// pythagoras theorem here!
		sprites[i].player_dist = std::sqrt(pow(sprites[i].x - player.x, 2) + pow(sprites[i].y - player.y, 2));
	}
	// TODO: Sort here!
	// Sort the sprites by distance
	sort_sprites(sprites);

	// Show monsters positions on the map
	for (int i = 0; i < sprites.size(); i++)
	{
		framebuffer.draw_rectangle(sprites[i].x * rect_w, sprites[i].y * rect_h, 5, 5, pack_color(255, 0, 0));
		draw_sprite(framebuffer, player, sprites[i], sprites_tex, depth_buffer);
	}
}

int main(int argc, char *argv[])
{
	FrameBuffer framebuffer{1024, 512};
	Map map;
	std::vector<Sprite> sprites{{3.523, 3.812, 2}, {1.834, 8.765, 0}, {5.323, 5.365, 1}, {4.123, 10.265, 2}};

	// player position x, y, initial player view direction (curr_angle between view direction and x axis), fov (1/3rd of screen)
	// The player's positions are relative to the map's width and height so 16 is like max
	Player player{3.456, 2.345, 1.523, M_PI / 3.};

	// 1/6 of 360 deg or 1/3pi rad!!!!!!!!!!
	// std::cout << M_PI / 3. << std::endl;

	Texture wall_tex("assets/walltext.png");
	if (wall_tex.count == 0)
	{
		std::cerr << "Failed to load wall textures" << std::endl;
		return -1;
	}

	Texture sprites_tex("assets/monsters.png");
	if (sprites_tex.count == 0)
	{
		std::cerr << "Failed to load sprite textures" << std::endl;
		return -1;
	}

	for (size_t frame_num = 0; frame_num < 360; frame_num++)
	{
		std::stringstream ss;

		// Set the name of the output frame (ppm) file
		// Fill 5 0's as initial string and then add the frame number
		ss << std::setfill('0') << std::setw(5) << frame_num << ".ppm";

		// incr by 1 deg in radians - 360 deg is about 6.28319 rad
		player.a += 2 * M_PI / 360;
		// std::cout << player.a << std::endl;

		render(framebuffer, map, player, sprites, wall_tex, sprites_tex);
		drop_ppm_image(ss.str(), framebuffer.img, framebuffer.w, framebuffer.h);
	}
}