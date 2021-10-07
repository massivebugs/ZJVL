#include "all.h"
#include "core/app.h"
#include "scene.h"
#include "asset/texture.h"

namespace ZJVL
{
	Scene::Scene()
		: texture(App::instance()->window_w, App::instance()->window_h),
		  shown_ms(0),
		  m_fade(false),
		  m_fade_in_ms(0),
		  m_fade_out_ms(0)
	{
		std::cout << "Creating Scene" << std::endl;
	};

	void Scene::load()
	{
		std::cout << "Loading Scene" << std::endl;

		// Create GameObjects 
		for (auto object : objects) {
			object->create(*this);
		}
	}

	void Scene::unload()
	{
		std::cout << "Unloading Scene" << std::endl;

		// Destroy GameObjects 
		for (auto object : objects) {
			object->destroy();
		}
	}

	void Scene::update(std::uint32_t dt)
	{
		// Update GameObjects
		for (auto object : objects) {
			object->update(*this, dt);
		}
	}

	void Scene::render(SDL_Renderer *renderer)
	{
		// Render GameObjects
		for (auto object : objects) {
			object->render(*this, renderer);
		}
		camera.render(*this, renderer);
	}

	void Scene::set_fade(std::uint32_t in_ms, std::uint32_t out_ms)
	{
		texture.set_blending();

		m_fade = true;
		m_fade_in_ms = in_ms;
		m_fade_out_ms = out_ms;
	}
}
