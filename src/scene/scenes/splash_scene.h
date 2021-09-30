#ifndef ZJVL_SCENE_SPLASHSCENE_H
#define ZJVL_SCENE_SPLASHSCENE_H

#include "all.h"
#include <SDL2/SDL.h>
#include "core/app.h"
#include "scene/scene.h"
#include "asset/texture.h"

namespace ZJVL
{
	class SplashScene : public Scene
	{
	public:
		SplashScene(const std::string &img_file, std::uint32_t display_ms = 0, const std::string &next_scene_id = "");

		void load() override;

		void unload() override;

		void update(std::uint32_t dt) override;

		void render(SDL_Renderer *renderer) override;

		void set_fading(std::uint32_t in_ms, std::uint32_t out_ms);

		Texture splash_image;
		std::uint32_t display_ms;
		std::string next_scene_id;

	private:
		std::uint32_t m_shown_ms;

		bool m_fade = false;
		std::uint32_t m_fade_in_ms;
		std::uint32_t m_fade_out_ms;

		void fade(std::uint32_t dt);
	};
}

#endif