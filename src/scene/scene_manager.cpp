#include "scene_manager.h"
#include "all.h"
#include <SDL2/SDL.h>
#include "scene.h"

namespace ZJVL
{
	void SceneManager::init(SDL_Renderer *renderer, int window_w, int window_h)
	{
		m_renderer = renderer;
		m_fade_rect.x = 0;
		m_fade_rect.y = 0;
		m_fade_rect.w = window_w;
		m_fade_rect.h = window_h;
		m_switch_delay = 0;
		m_switching = false;
	}

	void SceneManager::update(std::uint32_t dt)
	{
		if (m_switching)
		{
			m_switch_delay -= dt;

			if (m_switch_delay <= 0)
			{
				if (m_curr_scene != nullptr)
					m_curr_scene->unload();

				m_curr_scene = m_scenes[m_switch_scene_id];
				m_curr_scene->load();
				m_curr_scene->m_shown_ms = 0;

				m_switching = false;
			}
		}

		if (m_curr_scene != nullptr)
		{
			m_curr_scene->m_shown_ms += dt;
			m_curr_scene->update(dt);
		}
	};

	void SceneManager::render()
	{
		if (m_curr_scene != nullptr)
		{
			SDL_SetRenderTarget(m_renderer, m_curr_scene->texture.data);
			SDL_RenderClear(m_renderer);
			m_curr_scene->render(m_renderer);
			SDL_SetRenderTarget(m_renderer, NULL);
			SDL_RenderCopy(m_renderer, m_curr_scene->texture.data, NULL, NULL);

			if (m_curr_scene->m_fade)
			{
				if (m_curr_scene->m_shown_ms < m_curr_scene->m_fade_in_ms)
				{
					auto blend_rate = ((float)m_curr_scene->m_shown_ms / (float)m_curr_scene->m_fade_in_ms);
					SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 255 - (255 * blend_rate));
					SDL_RenderFillRect(m_renderer, &m_fade_rect);
					SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
				}
				else if (m_switching && m_switch_delay > 0 && m_switch_delay <= m_curr_scene->m_fade_out_ms)
				{
					auto blend_rate = ((float)m_switch_delay / (float)m_curr_scene->m_fade_out_ms);
					SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 255 - (255 * blend_rate));
					SDL_RenderFillRect(m_renderer, &m_fade_rect);
					SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
				}
			}
		}
	};

	void SceneManager::add(std::string id, std::shared_ptr<Scene> scene)
	{
		if (!has(id))
		{
			m_scenes[id] = scene;
		}
	}

	void SceneManager::switch_to(std::string id, std::uint32_t delay)
	{
		if (has(id) && m_switching == false)
		{
			m_switching = true;
			m_switch_scene_id = id;
			m_switch_delay = delay + (m_curr_scene == nullptr ? 0 : m_curr_scene->m_fade_out_ms);
		}
	}

	bool SceneManager::has(std::string id)
	{
		return (m_scenes.find(id) == m_scenes.end()) == false;
	};

	void SceneManager::remove(std::string id)
	{
		if (has(id))
			m_scenes.erase(id);
	};
}