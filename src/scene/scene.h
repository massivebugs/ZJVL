#ifndef ZJVL_SCENE_SCENE_H
#define ZJVL_SCENE_SCENE_H

#include "all.h"
#include <SDL2/SDL.h>
#include "asset/texture.h"

namespace ZJVL
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;

		// TODO: Add Camera

		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void update(std::uint32_t dt) = 0;
		virtual void render(SDL_Renderer *renderer) = 0;

		void set_fading(std::uint32_t in_ms, std::uint32_t out_ms);

		Texture texture;

	protected:
		friend class SceneManager;

		std::uint32_t m_shown_ms;
		bool m_fade;
		std::uint32_t m_fade_in_ms;
		std::uint32_t m_fade_out_ms;
	};
}
#endif