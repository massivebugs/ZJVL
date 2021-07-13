#ifndef ZJVL_FRAMEBUFFER_H
#define ZJVL_FRAMEBUFFER_H

#include <cstdint>
#include <vector>

namespace Engine
{
   struct FrameBuffer
   {
      int w, h;
      std::vector<uint32_t> img;
   };
}

#endif