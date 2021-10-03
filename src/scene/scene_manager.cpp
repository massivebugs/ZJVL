#include "scene_manager.h"
#include "all.h"
#include <SDL2/SDL.h>
#include "scene.h"

namespace ZJVL
{
	void SceneManager::init(SDL_Renderer *renderer, int window_w, int window_h)
	{
		m_renderer = renderer;
	}

	void SceneManager::update(std::uint32_t dt)
	{
		m_curr_scene->update(dt);
	};

	void SceneManager::render()
	{
		SDL_SetRenderTarget(m_renderer, m_curr_scene->texture.data);
		SDL_RenderClear(m_renderer);

		m_curr_scene->render(m_renderer);

		SDL_SetRenderTarget(m_renderer, NULL);
		SDL_RenderCopy(m_renderer, m_curr_scene->texture.data, NULL, NULL);
	};

	void SceneManager::add(std::string id, std::shared_ptr<Scene> scene)
	{
		if (!has(id))
		{
			m_scenes[id] = scene;
		}
	}

	void SceneManager::show(std::string id)
	{
		if (has(id))
		{
			if (m_curr_scene != nullptr)
				m_curr_scene->unload();

			m_curr_scene = m_scenes[id];
			m_curr_scene->load();
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