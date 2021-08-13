#ifndef ZJVL_SCENE_SCENE_SCENEMANAGER_H
#define ZJVL_SCENE_SCENE_SCENEMANAGER_H
#include "all.h"
#include "scene.h"
#include <SDL2/SDL.h>

namespace ZJVL
{
	namespace Scene
	{
		class SceneManager
		{
		public:
			void init(SDL_Renderer *renderer)
			{
				m_renderer = renderer;
			}

			void update(std::uint32_t dt)
			{
				m_curr_scene->update(dt);
			};

			void render()
			{
				m_curr_scene->render(m_renderer);
			};

			void change_to(std::shared_ptr<Scene> scene)
			{
				if (m_curr_scene != nullptr)
					m_curr_scene->unload();

				m_curr_scene = scene;
				m_curr_scene->load();
			};

		private:
			SDL_Renderer *m_renderer;
			std::shared_ptr<Scene> m_curr_scene;
		};
	}
}

#endif