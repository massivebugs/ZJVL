#include "all.h"
#include "core/app.h"
#include "scene.h"
#include "asset/texture.h"

namespace ZJVL
{
		Scene::Scene() : texture(App::instance()->window_w, App::instance()->window_h){};
}
