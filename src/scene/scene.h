#ifndef ZJVL_SCENE_SCENE_H
#define ZJVL_SCENE_SCENE_H

#include "all.h"
#include <SDL2/SDL.h>
#include "asset/texture.h"
#include "game_object.h"
#include "camera.h"

namespace ZJVL
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;

		void load();
		void unload();
		void update(std::uint32_t dt);
		void render(SDL_Renderer *renderer);

		void set_fade(std::uint32_t in_ms, std::uint32_t out_ms);

		Texture texture;
		std::uint32_t shown_ms;

		Camera camera;
		std::vector<std::shared_ptr<GameObject>> objects;

	protected:
		friend class SceneManager;

		bool m_fade;
		std::uint32_t m_fade_in_ms;
		std::uint32_t m_fade_out_ms;
	};
}
#endif