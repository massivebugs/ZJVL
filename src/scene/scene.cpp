#include "all.h"
#include "core/app.h"
#include "scene.h"
#include "asset/texture.h"

namespace ZJVL
{
	Scene::Scene()
		: texture(App::instance()->window_w, App::instance()->window_h){};

	void Scene::set_fading(std::uint32_t in_ms, std::uint32_t out_ms)
	{
		texture.set_blending();
		texture.set_alpha(0);

		m_fade = true;
		m_fade_in_ms = in_ms;
		m_fade_out_ms = out_ms;
	}

	void Scene::fade()
	{
		if (m_fade)
		{
			if (m_shown_ms < m_fade_in_ms)
			{
				std::cout << "fading in - " << m_shown_ms << std::endl;
				texture.set_alpha(255 * ((float)m_shown_ms / (float)m_fade_in_ms));
			}
			else
			{
				texture.set_alpha(255);
			}
		}
	}
}
