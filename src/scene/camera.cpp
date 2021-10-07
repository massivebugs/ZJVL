#include "all.h"
#include <SDL2/SDL.h>
#include "camera.h"
#include "game_object.h"

namespace ZJVL
{
	bool Camera::create(const Scene &scene)
	{
		return true;
	};

	void Camera::update(const Scene &scene, std::uint32_t dt){};
	void Camera::render(const Scene &scene, SDL_Renderer *renderer)
	{
		if (m_detached == false && !context.expired())
		{
			// TODO
		}
	};
	void Camera::destroy(){};
	void Camera::on_notify(Event &e){};

	void Camera::set_context(const std::shared_ptr<Actor> &actor)
	{
		if (actor == nullptr)
		{
			m_detached = true;
		}
		else
		{
			context = actor;
		}
	};
}