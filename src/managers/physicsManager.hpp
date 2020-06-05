//
// Created by superbob on 2020-06-02.
//

#ifndef CAPSTONE_SDL_PHYSICSMANAGER_HPP
#define CAPSTONE_SDL_PHYSICSMANAGER_HPP


#include <vector>
#include <memory>
#include <LinearMath/btVector3.h>
#include <glm/glm.hpp>
#include <functional>
#include "logic/collisionEvent.hpp"

class btDiscreteDynamicsWorld;
class btSequentialImpulseConstraintSolver;
class btDbvtBroadphase;
class btCollisionDispatcher;
class btDefaultCollisionConfiguration;

class btRigidBody;
class btTransform;
class btCollisionShape;

class Camera;
class SceneObject;

class PhysicsManager
{
	// order matters! These get initialized in the constructor.
	std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> m_dispatcher;
	std::unique_ptr<btDbvtBroadphase> m_broadphase;
	std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
	std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;
	
	std::vector<std::unique_ptr<btCollisionShape>> m_collisionShapes;
	
	btRigidBody *ground;
	btRigidBody *arena;
	
	btRigidBody *player;
	
	std::vector<btRigidBody *> enemies;
	std::vector<btRigidBody *> sparks;
	
	btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape);
	
	float getRandomPointOnArena();
	
	std::function<void(const CollisionEvent)> onArenaImpact;
	std::function<void(const CollisionEvent)> onPlayerGroundImpact;
	std::function<void(const CollisionEvent)> onTargetGroundImpact;
	std::function<void(const CollisionEvent)> onPlayerTargetImpact;
public:
	PhysicsManager();
	virtual ~PhysicsManager();
	
	int initWorld();
	void cleanup();
	
	void stepSimulation(float deltaTime);
	
	glm::vec3 getPlayerPos();
	glm::quat getPlayerRotation();
	float getPlayerSize();
	
	void applyForceToPlayer( float x, float y, float z, bool limit=true);
	void resetPlayer();
	void resizePlayer( float mass, float size );
	void setPlayerFriction( float friction);
	
	int addEnemy(SceneObject * object);
	glm::vec3 getEnemyPos(int id);
	glm::quat getEnemyRotation(int id);
	void resetEnemy(int id);
	void applyForceToEnemy(int id, float x, float y, float z, bool limit=true);
	
	void limitForce( btVector3 &impulse );
	
	// ---
	// Run after simulation, triggers callbacks
	// ---
	
	void handleCollisions();
	
	// ---
	// Game logic callbacks
	// ---
	
	void setOnArenaImpact( const std::function<void( const CollisionEvent )> &onArenaImpact );
	
	void setOnPlayerGroundImpact( const std::function<void( const CollisionEvent )> &onPlayerGroundImpact );
	
	void setOnEnemyGroundImpact( const std::function<void( const CollisionEvent )> &onEnemyGroundImpact );
	
	void setOnPlayerEnemyImpact( const std::function<void( const CollisionEvent )> &onPlayerEnemyImpact );
	
	// ---
	// Picking
	// ---
	
	glm::vec3 getMouseClickPosition( float screenX, float screenY, int screenWidth, int screenHeight, const Camera * camera  );
};


#endif //CAPSTONE_SDL_PHYSICSMANAGER_HPP
