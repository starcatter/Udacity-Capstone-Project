//
// Created by superbob on 2020-06-03.
//

#include <gfx/modelType.hpp>
#include <gfx/shaderType.hpp>
#include "sceneManager.hpp"

SceneManager::SceneManager( PhysicsManager *physics )
		: physics(physics), player {{0, 10, 0}, {1, 1, 1}, {0, 0, 0}}, board {{0, 0, 0}, {25, 5, 25}, {0, 0, 0}},
		  cursor {{0, 0, 0}, {0.25, 12, 0.25}, {0, 0, 0}}
{
	player.mesh = ModelType::normalCube;
	player.color = {0., 1., 1., 1};
	player.shader = ShaderType::lightedColor;
	
	board.mesh = ModelType::normalCube;
	board.color = {0.75, 0.75, 2., 1};
	board.shader = ShaderType::lightedColor;
	
	cursor.mesh = ModelType::cube;
	cursor.color = {1., 1.0, 1., 1};
	cursor.shader = ShaderType::simpleColor;
	
	camera.setTarget({-0.05, 1, -0.05});
}

void SceneManager::update( int stepMs )
{
	physics->stepSimulation(stepMs);
	
	syncSceneData();
	
	camera.setTarget(player.position);
}

void SceneManager::syncSceneData()
{
	float size = physics->getPlayerSize();
	
	player.position = physics->getPlayerPos();
	player.rotation = glm::quat {physics->getPlayerRotation()};
	player.scale = {size, size, size};
	
	for ( auto &enemy : enemies )
	{
		if ( !enemy.enabled ){ continue; }
		
		enemy.position = physics->getEnemyPos(enemy.index);
		enemy.rotation = glm::quat {physics->getEnemyRotation(enemy.index)};
	}
}

void SceneManager::addSparks( glm::vec3 vec, glm::vec3 vec1, float d )
{
	//TODO
}

SceneObject *SceneManager::addEnemy()
{
	SceneObject &object = enemies.emplace_back(glm::vec3 {5, 10, -5}, glm::vec3 {1, 1, 1}, glm::vec3 {0, 0, 0});
	
	object.enabled = true;
	object.shader = ShaderType::lightedColor;
	object.mesh = ModelType::normalCube;
	object.color = {1, 0, 0, 0};
	
	physics->addEnemy(&object);
	
	return &object;
}

void SceneManager::resetEnemies( int count )
{
	int activated = 0;
	for ( auto &enemy : enemies )
	{
		enemy.enabled = activated++ < count;
		
		physics->resetEnemy(enemy.index);
	}
}
