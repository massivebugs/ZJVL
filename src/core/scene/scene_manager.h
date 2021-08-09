#ifndef ZJVL_CORE_SCENE_SCENEMANAGER_H
#define ZJVL_CORE_SCENE_SCENEMANAGER_H
#include "all.h"
#include "scene.h"

namespace ZJVL
{
	namespace Core
	{
		class SceneManager
		{
		public:
			void update(std::uint32_t dt)
			{
				m_curr_scene->update(dt);
			};

			void render(){
			    m_curr_scene->render();
			};

			template <typename T>
			void change_to(std::shared_ptr<T> scene)
			{
				if (m_curr_scene != nullptr)
					m_curr_scene->unload();

				m_curr_scene = std::static_pointer_cast<Scene>(scene);
				m_curr_scene->load();
			};

		private:
			std::shared_ptr<Scene> m_curr_scene;
		};
	}
}

#endif