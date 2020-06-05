//
// Created by superbob on 2020-06-04.
//

#include "enemy.hpp"


glm::vec3 Enemy::getImpulse()
{
	// if the player is outside of the arena, AI tries to get back to the center
	if( glm::abs(player->position.x) >= 25 || glm::abs(player->position.z) >= 25 || player->position.y < 4){
		return {xPID.calculate(0,me->position.x),0,xPID.calculate(0,me->position.z)};
	}
	else {
		return {xPID.calculate(player->position.x,me->position.x),0,xPID.calculate(player->position.z,me->position.z)};
	}
}

void Enemy::resetPID()
{
	xPID.reset();
	yPID.reset();
}

Enemy::Enemy( SceneObject *me, const SceneObject *player )
		: xPID(0.10, 2.5, -2.5, 0.5, 0.10, 0.0025),
		  yPID(0.10, 2.5, -2.5, 0.5, 0.10, 0.0025),
		  me(me), player(player){}
