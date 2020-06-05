//
// Created by superbob on 2020-06-04.
//

#include "shaderManager.hpp"

void ShaderManager::initShaders()
{
	simpleShader = std::make_unique<Shader>("simple.vs","simple.fs");
	lightedShader = std::make_unique<Shader>("lighted.vs","lighted.fs");
}

void ShaderManager::cleanupShaders()
{

}

Shader * ShaderManager::getShader( ShaderType shader )
{
	switch (shader)
	{
		case ShaderType::simpleColor:return simpleShader.get();
		case ShaderType::lightedColor:return lightedShader.get();
	}
	throw std::runtime_error("Invalid shader type requested!");
}
