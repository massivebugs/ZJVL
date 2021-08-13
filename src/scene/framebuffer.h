#ifndef ZJVL_SCENE_FRAMEBUFFER_H
#define ZJVL_SCENE_FRAMEBUFFER_H

#include "all.h"
namespace ZJVL
{
   namespace Scene
   {
      struct FrameBuffer
      {
         int w, h;
         std::vector<uint32_t> img;
      };
   }
}

#endif