#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

#include "framebuffer.h"
#include "utils.h"

void FrameBuffer::set_pixel(const std::size_t x, const std::size_t y, const std::uint32_t color)
{
    assert(img.size() == w * h && x < w && y < h);
    img[x + y * w] = color;
}

void FrameBuffer::draw_rectangle(const std::size_t rect_x, const std::size_t rect_y, const std::size_t rect_w, const std::size_t rect_h, const std::uint32_t color)
{
    assert(img.size() == w * h);

    // Loop over rows and columns
    for (std::size_t curr_h = 0; curr_h < rect_h; curr_h++)
    {
        for (std::size_t curr_w = 0; curr_w < rect_w; curr_w++)
        {
            // Set the position of the pixel we will draw
            std::size_t x = rect_x + curr_w;
            std::size_t y = rect_y + curr_h;

            // Draw only what fits
            if (x < w && y < h)
                set_pixel(x, y, color);
        }
    }
}

void FrameBuffer::clear(const std::uint32_t color)
{
	// vector initialization
	// Create a vector of size window_w * window_h with color.
    img = std::vector<std::uint32_t>(w * h, color);
}