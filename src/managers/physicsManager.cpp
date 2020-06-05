//
// Created by superbob on 2020-06-02.
//

#include "physicsManager.hpp"

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <random>
#include <glm/detail/type_quat.hpp>
#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"

#include "scene/camera.hpp"

// use btSoftRigidDynamicsWorld instead of btDiscreteDynamicsWorld for fun effects...
// #include "BulletSoftBody/btSoftRigidDynamicsWorld.h"

PhysicsManager::PhysicsManager()
		: m_collisionConfiguration(std::make_unique<btDefaultCollisionConfiguration>()),
		  m_dispatcher(std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get())),
		  m_broadphase(std::make_unique<btDbvtBroadphase>()), m_solver(std::make_unique<btSequentialImpulseConstraintSolver>()),
		  m_dynamicsWorld(std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher.get(),
				  m_broadphase.get(),
				  m_solver.get(),
				  m_collisionConfiguration.get()))
{
	m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
	
}

PhysicsManager::~PhysicsManager()
{

}

int PhysicsManager::initWorld()
{
	// ---
	// create ground
	// ---
	btCollisionShape *groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	m_collisionShapes.emplace_back(groundShape);
	
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -15, 0));
	ground = createRigidBody(0., groundTransform, groundShape);
	ground->setUserPointer(nullptr);
	
	// ---
	// create arena
	// ---
	btTransform arenaTransform;
	arenaTransform.setIdentity();
	arenaTransform.setOrigin(btVector3(0, 0, 0));
	
	btBoxShape *arenaShape = new btBoxShape(btVector3(btScalar(25.), btScalar(5.), btScalar(25.)));
	arena = createRigidBody(0., arenaTransform, arenaShape);
	arena->setUserPointer(nullptr);
	
	
	// ---
	// create player
	// ---
	
	//btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	btBoxShape *colShape = new btBoxShape(btVector3(1., 1., 1.));
	m_collisionShapes.emplace_back(colShape);
	
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(btScalar(0.0), btScalar(10.), btScalar(0.0)));
	
	player = createRigidBody(10.f, startTransform, colShape);
	player->setFriction(0.2);
	player->setUserPointer(nullptr);
	
	return 0;
}

btRigidBody *PhysicsManager::createRigidBody( float mass, const btTransform &startTransform, btCollisionShape *shape )
{
	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = ( mass != 0.f );
	
	btVector3 localInertia(0, 0, 0);
	if ( isDynamic )
	{
		shape->calculateLocalInertia(mass, localInertia);
	}
	
	btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);
	
	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);
	
	btRigidBody *body = new btRigidBody(cInfo);
	
	body->setUserIndex(-1);
	m_dynamicsWorld->addRigidBody(body);
	
	return body;
}

glm::vec3 PhysicsManager::getPlayerPos()
{
	auto &origin = player->getWorldTransform().getOrigin();
	return {origin.x(), origin.y(), origin.z()};
}

glm::quat PhysicsManager::getPlayerRotation()
{
	const auto rotationQuat = player->getWorldTransform().getRotation();
	return glm::quat(rotationQuat.w(), rotationQuat.x(), rotationQuat.y(), rotationQuat.z());
}

glm::vec3 PhysicsManager::getEnemyPos( int index )
{
	auto &targetBox = enemies.at(index);
	auto &origin = targetBox->getWorldTransform().getOrigin();
	return {origin.x(), origin.y(), origin.z()};
}

glm::quat PhysicsManager::getEnemyRotation( int index )
{
	auto &targetBox = enemies.at(index);
	const auto rotationQuat = targetBox->getWorldTransform().getRotation();
	return glm::quat(rotationQuat.w(), rotationQuat.x(), rotationQuat.y(), rotationQuat.z());
}

void PhysicsManager::applyForceToEnemy( int index, float x, float y, float z, bool limit )
{
	btVector3 impulse {x, y, z};
	
	if ( limit ){ limitForce(impulse); }
	
	auto &targetBox = enemies.at(index);
	targetBox->applyCentralImpulse(impulse);
	targetBox->activate();
}

void PhysicsManager::resetEnemy( int index )
{
	auto &targetBox = enemies.at(index);
	targetBox->setLinearVelocity({0, 0, 0});
	targetBox->setAngularVelocity({0, 0, 0});
	targetBox->getWorldTransform().setOrigin({getRandomPointOnArena(), 10, getRandomPointOnArena()});
}

int PhysicsManager::addEnemy( SceneObject *object )
{
	object->index = enemies.size();
	
	btBoxShape *colShape = new btBoxShape(btVector3(1., 1., 1.));
	m_collisionShapes.emplace_back(colShape);
	
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(btScalar(getRandomPointOnArena()), btScalar(10.), btScalar(getRandomPointOnArena())));
	
	btRigidBody *targetBox = createRigidBody(10.f, startTransform, colShape);
	targetBox->setFriction(1.0);
	targetBox->setUserPointer(object);
	
	enemies.emplace_back(targetBox);
	
	return object->index;
}

void PhysicsManager::stepSimulation( float deltaTime )
{
	if ( m_dynamicsWorld )
	{
		handleCollisions();
		
		//auto &v = mainBox->getLinearVelocity();
		if ( player->getWorldTransform().getOrigin().length() > 100 )
		{
			resetPlayer();
		}
		
		m_dynamicsWorld->stepSimulation(deltaTime);
	}
}

void PhysicsManager::applyForceToPlayer( float x, float y, float z, bool limit )
{
	btVector3 impulse {x, y, z};
	
	if ( limit ){ limitForce(impulse); }
	player->applyCentralImpulse(impulse);
	player->activate();
	
}


void PhysicsManager::limitForce( btVector3 &impulse )
{
	while ( impulse.length() > 10 )
	{
		impulse *= 0.9f;
	}
	
}

void PhysicsManager::setPlayerFriction( float friction )
{
	player->setFriction(friction);
}

void PhysicsManager::cleanup()
{
	// TODO: cleanup physics
}

bool isContactBetween( btCollisionObject *a, btCollisionObject *b, btPersistentManifold *contactManifold )
{
	const btCollisionObject *obA = contactManifold->getBody0();
	const btCollisionObject *obB = contactManifold->getBody1();
	
	return contactManifold->getNumContacts() > 0 && ( a == obA || b == obA ) && ( a == obB || b == obB );
}

void PhysicsManager::handleCollisions()
{
	int numManifolds = m_dynamicsWorld->getDispatcher()->getNumManifolds();
	for ( int i = 0; i < numManifolds; i++ )
	{
		btPersistentManifold *contactManifold = m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		
		if ( isContactBetween(player, ground, contactManifold))
		{
			if ( onPlayerGroundImpact )
			{
				onPlayerGroundImpact({contactManifold, contactManifold->getContactPoint(0)});
			}
		}
		
		for ( const auto &enemy : enemies )
		{
			if ( isContactBetween(player, enemy, contactManifold))
			{
				if ( onPlayerTargetImpact )
				{
					onPlayerTargetImpact({contactManifold, contactManifold->getContactPoint(0)});
				}
			}
			
			if ( isContactBetween(enemy, ground, contactManifold))
			{
				if ( onTargetGroundImpact )
				{
					onTargetGroundImpact({contactManifold, contactManifold->getContactPoint(0)});
				}
			}
		}
	}
}

glm::vec3 PhysicsManager::getMouseClickPosition( float screenX, float screenY, int screenWidth, int screenHeight, const Camera *camera )
{
	btVector3 camPos {camera->Position.x, camera->Position.y, camera->Position.z};
	btVector3 camTarget {camera->Target.x, camera->Target.y, camera->Target.z};
	btVector3 cameraUp = btVector3(camera->Up.x, camera->Up.y, camera->Up.z);
	
	btVector3 rayFrom = camPos;
	
	float top = 1.f;
	float bottom = -1.f;
	float nearPlane = 1.f;
	float tanFov = ( top - bottom ) * 0.5f / nearPlane;
	float fov = btScalar(2.0) * btAtan(tanFov);
	
	btVector3 rayForward = ( camTarget - camPos );
	rayForward.normalize();
	float farPlane = 10000.f;
	rayForward *= farPlane;
	
	btVector3 hor;
	hor = rayForward.cross(cameraUp); ///
	hor.safeNormalize();
	
	btVector3 vertical = cameraUp;
	vertical = hor.cross(rayForward);
	vertical.safeNormalize();
	
	float tanfov = tanf(0.5f * fov);
	
	hor *= 2.f * farPlane * tanfov;
	vertical *= 2.f * farPlane * tanfov;
	
	btScalar aspect;
	float width = float(screenWidth);
	float height = float(screenHeight);
	
	aspect = width / height;
	
	hor *= aspect;
	
	btVector3 rayToCenter = rayFrom + rayForward;
	btVector3 dHor = hor * 1.f / width;
	btVector3 dVert = vertical * 1.f / height;
	
	btVector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * vertical;
	rayTo += btScalar(screenX) * dHor;
	rayTo -= btScalar(screenY) * dVert;
	
	
	btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);
	
	rayCallback.m_flags |= btTriangleRaycastCallback::kF_UseGjkConvexCastRaytest;
	m_dynamicsWorld->rayTest(rayFrom, rayTo, rayCallback);
	if ( rayCallback.hasHit())
	{
		btVector3 pickPos = rayCallback.m_hitPointWorld;
		btRigidBody *body = (btRigidBody *) btRigidBody::upcast(rayCallback.m_collisionObject);
		if ( body )
		{
			// got body...
		}
		
		return {pickPos.x(), pickPos.y(), pickPos.z()};
	}
	
	return {0, 0, 0};
}

void PhysicsManager::resetPlayer()
{
	player->setLinearVelocity({0, 0, 0});
	player->setAngularVelocity({0, 0, 0});
	player->getWorldTransform().setOrigin({0, 10, 0});
}


float PhysicsManager::getRandomPointOnArena()
{
	std::random_device rd;
	
	std::mt19937 eng(rd());
	
	std::uniform_int_distribution<> randomPointAboveArena(0., 2500.);
	
	return randomPointAboveArena(eng) / 100.;
}

void PhysicsManager::resizePlayer( float mass, float size )
{
	btVector3 localInertia(0, 0, 0);
	
	player->getCollisionShape()->setLocalScaling({size, size, size});
	player->getCollisionShape()->calculateLocalInertia(mass, localInertia);
	player->setMassProps(mass, localInertia);
	m_dynamicsWorld->getCollisionWorld()->updateSingleAabb(player);
}

float PhysicsManager::getPlayerSize()
{
	return player->getCollisionShape()->getLocalScaling().x();
}

void PhysicsManager::setOnArenaImpact( const std::function<void( const CollisionEvent )> &onArenaImpact )
{
	PhysicsManager::onArenaImpact = onArenaImpact;
}

void PhysicsManager::setOnPlayerGroundImpact( const std::function<void( const CollisionEvent )> &onPlayerGroundImpact )
{
	PhysicsManager::onPlayerGroundImpact = onPlayerGroundImpact;
}

void PhysicsManager::setOnEnemyGroundImpact( const std::function<void( const CollisionEvent )> &onEnemyGroundImpact )
{
	PhysicsManager::onTargetGroundImpact = onEnemyGroundImpact;
}

void PhysicsManager::setOnPlayerEnemyImpact( const std::function<void( const CollisionEvent )> &onPlayerEnemyImpact )
{
	PhysicsManager::onPlayerTargetImpact = onPlayerEnemyImpact;
}


