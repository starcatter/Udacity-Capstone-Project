//
// Created by superbob on 2020-06-03.
//

#ifndef CAPSTONE_SDL_SCENEMANAGER_HPP
#define CAPSTONE_SDL_SCENEMANAGER_HPP

#include <vector>
#include <list>

#include <glm/glm.hpp>
#include "physicsManager.hpp"
#include "scene/sceneObject.hpp"
#include "scene/camera.hpp"

class SceneManager
{
public:
	SceneManager( PhysicsManager *physics );
	
	const Camera & getCamera() const {return camera;}
	
	const std::vector<SceneObject> & getObjects() const {return objects;}
	
	void update(int stepMs);
	
	void setCursorPos(float x, float z){cursor.position.x = x; cursor.position.z = z; };
	
	const SceneObject &getPlayer() const {return player;}
	//const SceneObject &getTarget() const {return target;}
	const SceneObject &getBoard() const {return board;}
	const SceneObject &getCursor() const {return cursor;}
	const std::list<SceneObject> & getEnemies(){return enemies;}
	
	
	void addSparks( glm::vec3 vec, glm::vec3 vec1, float d );
	
	SceneObject * addEnemy();
	
	void resetEnemies(int count);

private:
	PhysicsManager * physics;
	
	Camera camera{ glm::vec3(15.0f, 15.0f, -15.0f) };
	
	SceneObject player;
	//SceneObject target;
	SceneObject board;
	
	std::list<SceneObject> enemies;
	//std::vector<SceneObject> sparks;
	
	// no physics
	SceneObject cursor;
	
	std::vector<SceneObject> objects;
	
	void syncSceneData();
};


#endif //CAPSTONE_SDL_SCENEMANAGER_HPP
