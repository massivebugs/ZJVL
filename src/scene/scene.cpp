#include "all.h"
#include "core/app.h"
#include "scene.h"
#include "asset/texture.h"

namespace ZJVL
{
	Scene::Scene()
		: texture(App::instance()->window_w, App::instance()->window_h),
		  m_shown_ms(0),
		  m_fade(false),
		  m_fade_in_ms(0),
		  m_fade_out_ms(0)
		{};

	void Scene::set_fading(std::uint32_t in_ms, std::uint32_t out_ms)
	{
		texture.set_blending();

		m_fade = true;
		m_fade_in_ms = in_ms;
		m_fade_out_ms = out_ms;
	}
}
