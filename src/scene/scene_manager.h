#ifndef ZJVL_SCENE_SCENE_SCENEMANAGER_H
#define ZJVL_SCENE_SCENE_SCENEMANAGER_H

#include "all.h"
#include <SDL2/SDL.h>
#include "scene.h"

namespace ZJVL
{
	class SceneManager
	{
	public:
		void init(SDL_Renderer *renderer, int window_w, int window_h)
		{
			m_renderer = renderer;
		}

		void update(std::uint32_t dt)
		{
			m_curr_scene->update(dt);
		};

		void render()
		{
			SDL_SetRenderTarget(m_renderer, m_curr_scene->texture.data);
			SDL_RenderClear(m_renderer);

			m_curr_scene->render(m_renderer);

			SDL_SetRenderTarget(m_renderer, NULL);
			SDL_RenderCopy(m_renderer, m_curr_scene->texture.data, NULL, NULL);
		};

		void add(std::string id, std::shared_ptr<Scene> scene)
		{
			if (!has(id))
			{
				m_scenes[id] = scene;
			}
		}

		void show(std::string id)
		{
			if (has(id))
			{
				if (m_curr_scene != nullptr)
					m_curr_scene->unload();

				m_curr_scene = m_scenes[id];
				m_curr_scene->load();
			}
		}

		bool has(std::string id)
		{
			return (m_scenes.find(id) == m_scenes.end()) == false;
		};

		void remove(std::string id)
		{
			if (has(id))
				m_scenes.erase(id);
		};

	private:
		SDL_Renderer *m_renderer;
		std::shared_ptr<Scene> m_curr_scene;
		std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
	};
}

#endif