#include "all.h"
#include "enemy.h"
#include "util/vec2.h"

namespace ZJVL
{
	Enemy::Enemy(const Vec2 &pos, const std::string &texture_path)
	    : Actor(pos, texture_path){};

	bool Enemy::create(const Scene &scene) { return true; };
	void Enemy::update(const Scene &scene, std::uint32_t dt){};
	void Enemy::render(const Scene &scene, SDL_Renderer *renderer){};
	void Enemy::destroy(){};
	void Enemy::on_notify(Event &e){};
}