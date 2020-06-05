//
// Created by superbob on 2020-06-04.
//

#include "collisionEvent.hpp"
#include "bullet/BulletCollision/btBulletCollisionCommon.h"

CollisionEvent::CollisionEvent( const btPersistentManifold * cm , const btManifoldPoint & pt ) :
		m_positionWorldOnB(pt.m_positionWorldOnB.x(), pt.m_positionWorldOnB.y(), pt.m_positionWorldOnB.z()),
		m_normalWorldOnB(pt.m_normalWorldOnB.x(), pt.m_normalWorldOnB.y(), pt.m_normalWorldOnB.z()),
		m_appliedImpulse(pt.m_appliedImpulse)
{
	if(cm->getBody0()->getUserPointer() != nullptr){
		object = static_cast<SceneObject *>(cm->getBody0()->getUserPointer());
	} else if(cm->getBody1()->getUserPointer() != nullptr){
		object = static_cast<SceneObject *>(cm->getBody1()->getUserPointer());
	} else {
		object = nullptr;
	}
}
