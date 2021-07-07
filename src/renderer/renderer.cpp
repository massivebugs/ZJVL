#include <cstdint>
#include <cassert>
#include <math.h>
#include <sstream>
#include <iomanip>

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"
#include "splash.h"
#include "utils/utils.h"

Renderer::Renderer()
{
	title = "Game";
	win_w = 1920;
	win_h = 1080;

	window = nullptr;
	renderer = nullptr;
	texture = nullptr;

	splash_surface = nullptr;
	splash_texture = nullptr;

	framebuffer = FrameBuffer{win_w, win_h};
}

Renderer::Renderer(const char *title, size_t win_w, size_t win_h)
{
	this->title = title;
	this->win_w = win_w;
	this->win_h = win_h;

	window = nullptr;
	renderer = nullptr;
	texture = nullptr;

	splash_surface = nullptr;
	splash_texture = nullptr;

	framebuffer = FrameBuffer{win_w, win_h};
}

bool Renderer::init()
{
	// Initialize SDL window
	window = SDL_CreateWindow(
	    title,
	    SDL_WINDOWPOS_CENTERED,
	    SDL_WINDOWPOS_CENTERED,
	    win_w,
	    win_h,
	    SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Failed to create SDL Window. SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}

	// Initialize SDL renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_UpdateWindowSurface(window);

	// https: //stackoverflow.com/questions/21007329/what-is-an-sdl-renderer
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, framebuffer.w, framebuffer.h);

	// TODO: Remove later
	// Texture wall_tex("assets/walltext.png");
	// if (wall_tex.count == 0)
	// {
	// 	std::cerr << "Failed to load wall textures" << std::endl;
	// 	return false;
	// }

	// Texture entities_tex("assets/monsters.png");
	// if (entities_tex.count == 0)
	// {
	// 	std::cerr << "Failed to load entity textures" << std::endl;
	// 	return false;
	// }

	return true;
}

void Renderer::cleanup()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

bool Renderer::render_splash(const Splash &splash_image)
{
	std::cout << "Rendering splash..." << std::endl;

	// Display splashes here
	splash_surface = IMG_Load(splash_image.img_path);
	if (splash_surface == nullptr)
	{
		std::cout << "Failed to load splash image . SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	splash_texture = SDL_CreateTextureFromSurface(renderer, splash_surface);
	if (splash_texture == nullptr)
	{
		std::cout << "Failed to load splash image . SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, splash_texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Delay(splash_image.display_ms);

	SDL_FreeSurface(splash_surface);
	SDL_DestroyTexture(splash_texture);
	return true;
}

void Renderer::draw_map()
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

void Renderer::draw_entity(Entity &player, Entity &entity)
{
	// https://www.youtube.com/watch?v=BJ0-3kERCwc
	// https://www.youtube.com/watch?v=MHoFqRyeP3o の2:52を見てみるとちょっとわかるかも
	// https://boxbase.org/entries/2014/jun/23/why-radians/ Why we use radians
	// entity_dir is like the angle between the x axis and curr entity's location
	float entity_dir = atan2(entity.y - player.y, entity.x - player.x);

	// TODO: Wtf is this?!
	while (entity_dir - player.angle > M_PI) // while entity in the oppsite+ direction
		entity_dir -= 2 * M_PI;		 // remove unncesessary periods from the relative direction
	while (entity_dir - player.angle < -M_PI)
		entity_dir += 2 * M_PI;

	size_t entity_size = std::min(1000, static_cast<int>(framebuffer.h / entity.dist));

	// Kind of like when drawing the wall. Gets the upper left coordinates of the entity to draw
	int w_offset = (entity_dir - player.angle) * (framebuffer.w / 2) / (player.fov) + (framebuffer.w / 2) / 2 - entity_size / 2;
	int h_offset = (framebuffer.h / 2) - (entity_size / 2);

	for (size_t i = 0; i < entity_size; i++)
	{
		if (w_offset + int(i) < 0 || w_offset + i >= framebuffer.w / 2)
			continue;

		// Don't draw the entity if it is behind a wall
		if (depth_buffer[w_offset + i] <= entity.dist)
			continue;

		size_t entity_col = (float(entities_tex.size) / float(entity_size)) * i;

		std::vector<uint32_t> column = entities_tex.get_scaled_column(entity.texture_index, entity_col, entity_size);
		for (int curr_height = 0; curr_height < column.size(); curr_height++)
		{
			if (is_transparent_pixel(column[curr_height]))
				continue;

			framebuffer.set_pixel(framebuffer.w / 2 + w_offset + i, (framebuffer.h / 2) - (entity_size / 2) + curr_height, column[curr_height]);
		}
	}
}

void Renderer::cast_ray(Entity &player)
{
	// window_w so we can render the whole screen width
	for (std::size_t i = 0; i < framebuffer.w / 2; i++)
	{
		// fov * i / float(window_w / 2) increasingly gives higher value until it reaches 100% of fov, so that we can actually rotate the ray
		// curr_angle is the current viewing point, directly ahead. fov / 2 is setting the current view to render to be the left peripheral
		float curr_angle = player.angle - player.fov / 2 + player.fov * i / float(framebuffer.w / 2);
		// std::cout << player.angle << std::endl;

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
				// float bb = (h * cos(curr_angle - player.angle));
				// Wall_height is too big...?
				std::size_t wall_height = framebuffer.h / (h * cos(curr_angle - player.angle));
				std::size_t texture_index = map.get(view_y, view_x);

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
					// std::size_t aa = (framebuffer.h / 2) - (wall_height / 2) + curr_height;
					framebuffer.set_pixel(framebuffer.w / 2 + i, (framebuffer.h / 2) - (wall_height / 2) + curr_height, column[curr_height]);
				}
				break;
			}
		}
	}
}

bool Renderer::render(Entity &player, std::vector<Entity> &entities)
{

	// Clear and reset framebuffer image to white
	framebuffer.clear(pack_color(255, 255, 255));

	// Size of blocks on the map (wall, etc)
	rect_w = (framebuffer.w / 2) / map.w;
	rect_h = framebuffer.h / map.h;

	// Depth map of the walls
	depth_buffer = std::vector<float>(framebuffer.w / 2, 1e3);

	draw_map();

	cast_ray(player);

	// Show player position on the map
	framebuffer.draw_rectangle(player.x * rect_w, player.y * rect_h, 5, 5, pack_color(0, 255, 0));

	// Store sprite distance relative to player
	for (int i = 0; i < entities.size(); i++)
	{
		// pythagoras theorem here!
		entities[i].dist = std::sqrt(pow(entities[i].x - player.x, 2) + pow(entities[i].y - player.y, 2));
	}

	// Sort the entities by distance
	sort_entities(entities);

	// Show monsters positions on the map
	for (int i = 0; i < entities.size(); i++)
	{
		framebuffer.draw_rectangle(entities[i].x * rect_w, entities[i].y * rect_h, 5, 5, pack_color(255, 0, 0));
		draw_entity(player, entities[i]);
	}

	SDL_UpdateTexture(texture, NULL, reinterpret_cast<void *>(framebuffer.img.data()), framebuffer.w * 4);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	return true;
}