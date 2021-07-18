#ifndef ZJVL_CORE_FRAMEBUFFER_H
#define ZJVL_CORE_FRAMEBUFFER_H

#include <cstdint>
#include <vector>

namespace ZJVL
{
   namespace Core
   {
      struct FrameBuffer
      {
         int w, h;
         std::vector<uint32_t> img;
      };
   }
}

#endif