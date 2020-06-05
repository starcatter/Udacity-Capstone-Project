//
// Created by superbob on 2020-06-04.
//

#ifndef CAPSTONE_SDL_COLLISIONEVENT_HPP
#define CAPSTONE_SDL_COLLISIONEVENT_HPP

#include <glm/glm.hpp>
#include <scene/sceneObject.hpp>

class btPersistentManifold;

class btManifoldPoint;

struct CollisionEvent
{
	CollisionEvent( const btPersistentManifold * cm, const btManifoldPoint &pt );
	
	glm::vec3 m_positionWorldOnB;
	glm::vec3 m_normalWorldOnB;
	float m_appliedImpulse;
	
	// collided object, only enemies have this set
	SceneObject *object;
};


#endif //CAPSTONE_SDL_COLLISIONEVENT_HPP
