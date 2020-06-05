//
// Created by superbob on 2020-06-04.
//

#include <stdexcept>
#include "gameLogic.hpp"

GameLogic::GameLogic( SceneManager *scene, PhysicsManager *physics )
		: scene(scene), physics(physics)
{
	physics->setOnPlayerEnemyImpact(std::bind(&GameLogic::handlePlayerOnEnemyImpact, this, std::placeholders::_1));
	physics->setOnPlayerGroundImpact(std::bind(&GameLogic::handlePlayerGroundImpact, this, std::placeholders::_1));
	physics->setOnEnemyGroundImpact(std::bind(&GameLogic::handleEnemyGroundImpact, this, std::placeholders::_1));
	physics->setOnArenaImpact(std::bind(&GameLogic::handleArenaImpact, this, std::placeholders::_1));
	
	// add first enemy
	addEnemy();
}

void GameLogic::handlePlayerOnEnemyImpact( CollisionEvent e )
{
	physics->applyForceToEnemy(0, e.m_appliedImpulse*10., 0, false);
}

void GameLogic::handlePlayerGroundImpact( CollisionEvent e )
{
	enemyCount = 1;
	mainBoxSize = 1;
	mainBoxMass = 10;
	physics->resizePlayer(mainBoxMass, mainBoxSize);
	
	physics->resetPlayer();
	scene->resetEnemies(enemyCount);
}

void GameLogic::handleEnemyGroundImpact( CollisionEvent e )
{
	e.object->enabled = false;
	
	if( countActiveEnemies() == 0){
		growPlayer();
		resetPidStates();
		scene->resetEnemies(enemyCount++);
		addEnemy();
	}
}

int GameLogic::countActiveEnemies() const
{
	const auto & enemies = scene->getEnemies();
	int activeEnemies = std::count_if(enemies.begin(), enemies.end(), []( const SceneObject & e){ return e.enabled; });
	return activeEnemies;
}

void GameLogic::addEnemy()
{
	auto enemyObj = scene->addEnemy();
	enemyAi.emplace_back(enemyObj, &scene->getPlayer());
}

void GameLogic::handleArenaImpact( CollisionEvent e )
{
	// TODO: implement sparks!
	// scene->addSparks(e.m_positionWorldOnB, e.m_normalWorldOnB, e.m_appliedImpulse);
}

void GameLogic::growPlayer()
{
	mainBoxSize = mainBoxSize + 0.25;
	mainBoxMass = mainBoxMass * 1.25;
	
	physics->resizePlayer(mainBoxMass, mainBoxSize);
	physics->applyForceToPlayer(0, mainBoxMass, 0);
}

void GameLogic::update()
{
	for ( auto &ai : enemyAi )
	{
		auto object = ai.getObject();
		if(object->enabled)
		{
			auto impulse = ai.getImpulse();
			physics->applyForceToEnemy(object->index, impulse.x, impulse.y, impulse.z);
		}
	}
}

float GameLogic::getMainBoxMass() const
{
	return mainBoxMass;
}

void GameLogic::resetPidStates()
{
	for ( auto &ai : enemyAi )
	{
		ai.resetPID();
	}
}
