#ifndef ZJVL_SCENE_SPLASHSCENE_H
#define ZJVL_SCENE_SPLASHSCENE_H

#include "all.h"
#include <SDL2/SDL.h>
#include "core/app.h"
#include "scene/scene_manager.h"
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

		Texture splash_image;
		std::uint32_t display_ms;
		std::string next_scene_id;
	};
}

#endif