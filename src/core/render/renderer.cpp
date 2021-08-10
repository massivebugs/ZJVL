// #include "all.h"
// #include "renderer.h"
// #include "core/scene/splash.h"
// #include "core/scene/scene.h"

// namespace ZJVL
// {
// 	namespace Core
// 	{
// 		Renderer::Renderer() : framebuffer{1024, 512} {};
// 		Renderer::Renderer(int w, int h) : framebuffer{w, h} {}

// 		bool Renderer::init()
// 		{
// 			// TODO: Remove later
// 			// Texture wall_tex("assets/walltext.png");
// 			// if (wall_tex.count == 0)
// 			// {
// 			// 	std::cerr << "Failed to load wall textures" << std::endl;
// 			// 	return false;
// 			// }

// 			// Texture entities_tex("assets/monsters.png");
// 			// if (entities_tex.count == 0)
// 			// {
// 			// 	std::cerr << "Failed to load entity textures" << std::endl;
// 			// 	return false;
// 			// }

// 			return true;
// 		}

// 		void Renderer::cleanup()
// 		{
// 		}

// 		void Renderer::set_scene(Scene &scene)
// 		{
// 			this->scene = scene;
// 		}

// 		void Renderer::draw_map()
// 		{
// 			// Render the map
// 			for (std::size_t row = 0; row < scene.map.h; row++)
// 			{
// 				for (std::size_t col = 0; col < scene.map.w; col++)
// 				{
// 					// Do nothing with empty spaces on the map
// 					if (scene.map.is_empty(row, col))
// 						continue;

// 					// position of the part we are drawing
// 					// so it would draw rect_w * rect_h size rectangle on position i * j of the map
// 					std::size_t rect_y = row * rect_h;
// 					std::size_t rect_x = col * rect_w;

// 					std::size_t texture_index = scene.map.get(row, col);
// 					assert(texture_index < wall_tex.count);

// 					// The color is taken from the upper left pixel of the texture for the map
// 					draw_rectangle(rect_x, rect_y, rect_w, rect_h, wall_tex.get(0, 0, texture_index));
// 				}
// 			}
// 		}

// 		void Renderer::draw_entity(Entity &entity)
// 		{
// 			// https://www.youtube.com/watch?v=BJ0-3kERCwc
// 			// https://www.youtube.com/watch?v=MHoFqRyeP3o の2:52を見てみるとちょっとわかるかも
// 			// https://boxbase.org/entries/2014/jun/23/why-radians/ Why we use radians
// 			// entity_dir is like the angle between the x axis and curr entity's location
// 			float entity_dir = atan2(entity.y - scene.player.y, entity.x - scene.player.x);

// 			// TODO: Wtf is this?!
// 			while (entity_dir - scene.player.angle > M_PI) // while entity in the oppsite+ direction
// 				entity_dir -= 2 * M_PI;		       // remove unncesessary periods from the relative direction
// 			while (entity_dir - scene.player.angle < -M_PI)
// 				entity_dir += 2 * M_PI;

// 			size_t entity_size = std::min(1000, static_cast<int>(framebuffer.h / entity.dist));

// 			// Kind of like when drawing the wall. Gets the upper left coordinates of the entity to draw
// 			int w_offset = (entity_dir - scene.player.angle) * (framebuffer.w / 2) / (scene.player.fov) + (framebuffer.w / 2) / 2 - entity_size / 2;
// 			int h_offset = (framebuffer.h / 2) - (entity_size / 2);

// 			for (size_t i = 0; i < entity_size; i++)
// 			{
// 				if (w_offset + int(i) < 0 || w_offset + i >= framebuffer.w / 2)
// 					continue;

// 				// Don't draw the entity if it is behind a wall
// 				if (depth_buffer[w_offset + i] <= entity.dist)
// 					continue;

// 				size_t entity_col = (float(entities_tex.size) / float(entity_size)) * i;

// 				std::vector<uint32_t> column = entities_tex.get_scaled_column(entity.texture_index, entity_col, entity_size);
// 				for (int curr_height = 0; curr_height < column.size(); curr_height++)
// 				{
// 					if (is_transparent_pixel(column[curr_height]))
// 						continue;

// 					set_pixel(framebuffer.w / 2 + w_offset + i, (framebuffer.h / 2) - (entity_size / 2) + curr_height, column[curr_height]);
// 				}
// 			}
// 		}

// 		void Renderer::cast_ray()
// 		{
// 			// window_w so we can render the whole screen width
// 			for (std::size_t i = 0; i < framebuffer.w / 2; i++)
// 			{
// 				// fov * i / float(window_w / 2) increasingly gives higher value until it reaches 100% of fov, so that we can actually rotate the ray
// 				// curr_angle is the current viewing point, directly ahead. fov / 2 is setting the current view to render to be the left peripheral
// 				float curr_angle = scene.player.angle - scene.player.fov / 2 + scene.player.fov * i / float(framebuffer.w / 2);
// 				// std::cout << player.angle << std::endl;

// 				// soh cah toa
// 				// hypothenuse = h, adjacent = a, opposite = o
// 				// by setting an arbitrary hypotheneuse length, we can calculate the length of a && o using trig functions
// 				// https://www.quora.com/What-is-the-purpose-of-the-sin-cos-and-tan-functions
// 				// hypothenuse h, and the rate we are extending it h_step
// 				const float h_step = 0.01;
// 				for (float h = 0; h < 20; h += h_step)
// 				{
// 					// offset_x + h * a / h so we just get a!
// 					float view_x = scene.player.x + h * cos(curr_angle);
// 					float view_y = scene.player.y + h * sin(curr_angle);

// 					std::size_t pix_x = view_x * rect_w;
// 					std::size_t pix_y = view_y * rect_h;

// 					// This draws the visibility cone
// 					set_pixel(pix_x, pix_y, pack_color(160, 160, 160));
// 					// std::cout << view_x << ':' << view_y << std::endl;

// 					// ray is touching a wall
// 					if (scene.map.is_empty(view_y, view_x) == false)
// 					{
// 						// Store the depth of the map
// 						depth_buffer[i] = h;

// 						// http://www.permadi.com/tutorial/raycast/rayc4.html
// 						// float bb = (h * cos(curr_angle - player.angle));
// 						// Wall_height is too big...?
// 						std::size_t wall_height = framebuffer.h / (h * cos(curr_angle - scene.player.angle));
// 						std::size_t texture_index = scene.map.get(view_y, view_x);

// 						// Count texture pixels
// 						float hit;
// 						// Check if the position we are at is almost a whole number (6.01 etc due to hypotheneuse length offset)
// 						float offset = view_x - (int)view_x;
// 						if (offset < 1 - h_step && offset > h_step)
// 						{
// 							// We hit a wall on the x plane!
// 							hit = view_x - (int)view_x; // because view_x represents how many blocks
// 						}
// 						else
// 						{
// 							// We hit a wall on the y plane!
// 							hit = view_y - (int)view_y;
// 						}
// 						// The current column of the texture we need to extract pixels from
// 						int texture_col = wall_tex.size * hit;

// 						assert(texture_col < wall_tex.size);

// 						std::vector<uint32_t> column = wall_tex.get_scaled_column(texture_index, texture_col, wall_height);

// 						for (int curr_height = 0; curr_height < column.size(); curr_height++)
// 						{
// 							// std::size_t aa = (framebuffer.h / 2) - (wall_height / 2) + curr_height;
// 							set_pixel(framebuffer.w / 2 + i, (framebuffer.h / 2) - (wall_height / 2) + curr_height, column[curr_height]);
// 						}
// 						break;
// 					}
// 				}
// 			}
// 		}

// 		FrameBuffer *Renderer::render()
// 		{

// 			// Clear and reset framebuffer image to white
// 			clear(pack_color(255, 255, 255));

// 			// Size of blocks on the map (wall, etc)
// 			rect_w = (framebuffer.w / 2) / scene.map.w;
// 			rect_h = framebuffer.h / scene.map.h;

// 			// Depth map of the walls
// 			depth_buffer = std::vector<float>(framebuffer.w / 2, 1e3);

// 			draw_map();

// 			cast_ray();

// 			// Show player position on the map
// 			draw_rectangle(scene.player.x * rect_w, scene.player.y * rect_h, 5, 5, pack_color(0, 255, 0));

// 			// Store sprite distance relative to player
// 			for (int i = 0; i < scene.entities.size(); i++)
// 			{
// 				// pythagoras theorem here!
// 				scene.entities[i].dist = std::sqrt(pow(scene.entities[i].x - scene.player.x, 2) + pow(scene.entities[i].y - scene.player.y, 2));
// 			}

// 			// Sort the entities by distance
// 			scene.sort_entities();

// 			// Show monsters positions on the map
// 			for (int i = 0; i < scene.entities.size(); i++)
// 			{
// 				draw_rectangle(scene.entities[i].x * rect_w, scene.entities[i].y * rect_h, 5, 5, pack_color(255, 0, 0));
// 				draw_entity(scene.entities[i]);
// 			}

// 			return &framebuffer;
// 		}

// 		void Renderer::set_pixel(const std::size_t x, const std::size_t y, const std::uint32_t color)
// 		{
// 			if (framebuffer.img.size() == framebuffer.w * framebuffer.h && x < framebuffer.w && y < framebuffer.h)
// 				framebuffer.img[x + y * framebuffer.w] = color;
// 		}

// 		void Renderer::draw_rectangle(const std::size_t rect_x, const std::size_t rect_y, const std::size_t rect_w, const std::size_t rect_h, const std::uint32_t color)
// 		{
// 			// assert(framebuffer.img.size() == w * h);

// 			// Loop over rows and columns
// 			for (std::size_t curr_h = 0; curr_h < rect_h; curr_h++)
// 			{
// 				for (std::size_t curr_w = 0; curr_w < rect_w; curr_w++)
// 				{
// 					// Set the position of the pixel we will draw
// 					std::size_t x = rect_x + curr_w;
// 					std::size_t y = rect_y + curr_h;

// 					// Draw only what fits - do we need this?
// 					if (x < framebuffer.w && y < framebuffer.h)
// 						set_pixel(x, y, color);
// 				}
// 			}
// 		}

// 		void Renderer::clear(const std::uint32_t color)
// 		{
// 			// vector initialization
// 			// Create a vector of size window_w * window_h with color.
// 			framebuffer.img = std::vector<std::uint32_t>(framebuffer.w * framebuffer.h, color);
// 		}

// 		bool Renderer::is_transparent_pixel(const uint32_t &color)
// 		{
// 			std::uint8_t opacity = color >> 24 & 255;
// 			return opacity == 0;
// 		}

// 		uint32_t Renderer::pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
// 		{
// 			return (a << 24) + (b << 16) + (g << 8) + r;
// 		}

// 	}

// }