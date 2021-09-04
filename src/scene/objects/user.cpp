#include "all.h"
#include "user.h"

namespace ZJVL
{
	User::User(const std::string &name, std::size_t texture_index)
	    : Actor(name, texture_index){};

	bool User::create(const Scene &scene) { return true; };
	void User::update(std::uint32_t dt){};
	void User::render(SDL_Renderer *renderer){};
	void User::destroy(){};
	void User::on_notify(Event &e){};
}