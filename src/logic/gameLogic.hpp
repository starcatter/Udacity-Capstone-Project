//
// Created by superbob on 2020-06-04.
//

#ifndef CAPSTONE_SDL_GAMELOGIC_HPP
#define CAPSTONE_SDL_GAMELOGIC_HPP

#include "managers/physicsManager.hpp"
#include <scene/sceneObject.hpp>
#include "scene/camera.hpp"
#include "managers/sceneManager.hpp"
#include "logic/collisionEvent.hpp"
#include "logic/enemy.hpp"

class GameLogic
{
	SceneManager * scene;
	PhysicsManager * physics;
	
	std::vector<Enemy> enemyAi;
	
	int enemyCount{1};
	float mainBoxSize{1};
	float mainBoxMass{10};
	
	void growPlayer();
	void addEnemy();
	void resetPidStates();
	int countActiveEnemies() const;
public:
	GameLogic( SceneManager *scene, PhysicsManager *physics );
	
	void handlePlayerOnEnemyImpact(const CollisionEvent e);
	void handlePlayerGroundImpact(const CollisionEvent e);
	void handleEnemyGroundImpact(const CollisionEvent e);
	void handleArenaImpact( CollisionEvent e);
	
	// update enemies
	void update();
	
	float getMainBoxMass() const;
};


#endif //CAPSTONE_SDL_GAMELOGIC_HPP
