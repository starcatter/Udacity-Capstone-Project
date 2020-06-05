//
// Created by superbob on 2020-06-03.
//

#include "sceneObject.hpp"

glm::mat4 SceneObject::getMatrix() const{
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 RotationMatrix = glm::toMat4(rotation);
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	
	return TranslationMatrix * RotationMatrix * ScaleMatrix;
}
