//
// Created by superbob on 2020-06-03.
//

#ifndef CAPSTONE_SDL_SCENEOBJECT_HPP
#define CAPSTONE_SDL_SCENEOBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "gfx/modelType.hpp"
#include "gfx/shaderType.hpp"

struct SceneObject{
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	
	glm::vec4 color;
	
	ModelType mesh;
	ShaderType shader;
	
	// used for enemies/sparks
	int index{-1};
	// only render enabled objects
	bool enabled{true};
	
	SceneObject( const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation ) :
			position(position), scale(scale), rotation(rotation){}
	
	SceneObject( const glm::vec3 &position ) : position(position), scale({1.f, 1.f, 1.f}), rotation({0.f, 0.f, 0.f}){}
	
	glm::mat4 getMatrix() const;
};

#endif //CAPSTONE_SDL_SCENEOBJECT_HPP
