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
		void init(SDL_Renderer *renderer, int window_w, int window_h);

		void update(std::uint32_t dt);

		void render();

		void add(std::string id, std::shared_ptr<Scene> scene);

		void switch_to(std::string id, std::uint32_t delay = 0);

		bool has(std::string id);

		void remove(std::string id);

	private:
		SDL_Renderer *m_renderer;
		SDL_Rect m_fade_rect;
		std::shared_ptr<Scene> m_curr_scene;
		std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

		bool m_switching;
		std::string m_switch_scene_id;
		std::int64_t m_switch_delay;
	};
}

#endif