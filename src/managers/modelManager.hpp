//
// Created by superbob on 2020-06-03.
//

#ifndef CAPSTONE_SDL_MODELMANAGER_HPP
#define CAPSTONE_SDL_MODELMANAGER_HPP

#include <vector>
#include "gfx/modelType.hpp"

struct MeshData{
	unsigned int vertexCount;
	unsigned int VBO;
	unsigned int VAO;
};

class ModelManager
{
	static std::vector<float> sparkModel; // single triangle, used for sparks
	static std::vector<float> cubeModel; // basic cube
	static std::vector<float> normalCubeModel; // cube /w normals
	
	MeshData sparkData;
	MeshData cubeData;
	MeshData normalCubeData;
public:
	void initModels();
	void cleanupModels();
	
	const MeshData & getMeshData( ModelType model);
};


#endif //CAPSTONE_SDL_MODELMANAGER_HPP
