//
// Created by superbob on 2020-06-04.
//

#ifndef CAPSTONE_SDL_ENEMY_HPP
#define CAPSTONE_SDL_ENEMY_HPP

#include <glm/glm.hpp>
#include <pid/pid.h>
#include <scene/sceneObject.hpp>

class PhysicsManager;

class Enemy
{
	PID xPID;
	PID yPID;
	
	SceneObject * me;
	const SceneObject * player;
public:
	Enemy( SceneObject *me, const SceneObject *player );
	
	SceneObject * getObject(){return me;}
	glm::vec3 getImpulse();
	
	void resetPID();
};


#endif //CAPSTONE_SDL_ENEMY_HPP
