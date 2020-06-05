//
// Created by superbob on 2020-06-03.
//

#include <limits>
#include <GL/glew.h>
#include <stdexcept>

#include "managers/modelManager.hpp"
#include "gfx/modelType.hpp"

std::vector<float> ModelManager::sparkModel{
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		};

std::vector<float> ModelManager::cubeModel{
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
};

std::vector<float> ModelManager::normalCubeModel {
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
	1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
	1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
	1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
	
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
	-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
	-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
	
	1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
	1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
	1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
	1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
	1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
	1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
	
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
	1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
	1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
	1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
	
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f
};

void ModelManager::initModels()
{
	// ---
	// spark
	// ---
	
	sparkData.vertexCount = sparkModel.size()/3;
	
	glGenBuffers(1, &sparkData.VBO);
	glGenVertexArrays(1, &sparkData.VAO);
	
	glBindVertexArray(sparkData.VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, sparkData.VBO);
	glBufferData(GL_ARRAY_BUFFER, sparkModel.size()*sizeof(float), sparkModel.data(), GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// ---
	// cube
	// ---
	
	cubeData.vertexCount = cubeModel.size()/3;
	
	glGenBuffers(1, &cubeData.VBO);
	glGenVertexArrays(1, &cubeData.VAO);
	
	glBindVertexArray(cubeData.VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, cubeData.VBO);
	glBufferData(GL_ARRAY_BUFFER, cubeModel.size()*sizeof(float), cubeModel.data(), GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// ---
	// normal cube
	// ---
	
	normalCubeData.vertexCount = normalCubeModel.size()/6;
	
	glGenBuffers(1, &normalCubeData.VBO);
	glGenVertexArrays(1, &normalCubeData.VAO);
	
	glBindVertexArray(normalCubeData.VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, normalCubeData.VBO);
	glBufferData(GL_ARRAY_BUFFER, normalCubeModel.size()*sizeof(float), normalCubeModel.data(), GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void ModelManager::cleanupModels()
{
	glDeleteBuffers(1, &cubeData.VBO);
	glDeleteVertexArrays(1, &cubeData.VAO);
	
	glDeleteBuffers(1, &normalCubeData.VBO);
	glDeleteVertexArrays(1, &normalCubeData.VAO);
}

const MeshData &ModelManager::getMeshData( ModelType model )
{
	switch(model){
		case ModelType::spark:
			return sparkData;
		case ModelType::cube:
			return cubeData;
		case ModelType::normalCube:
			return normalCubeData;
		default:
			throw std::runtime_error("Invalid model type requested!");
	}
}
