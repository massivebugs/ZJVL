#include "all.h"
#include "enemy.h"

namespace ZJVL
{
	Enemy::Enemy(const std::string &name, std::size_t texture_index)
	    : Actor(name, texture_index){};

	bool Enemy::create(const Scene &scene) { return true; };
	void Enemy::update(std::uint32_t dt){};
	void Enemy::render(SDL_Renderer *renderer){};
	void Enemy::destroy(){};
	void Enemy::on_notify(Event &e){};
}