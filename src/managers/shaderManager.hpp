//
// Created by superbob on 2020-06-04.
//

#ifndef CAPSTONE_SDL_SHADERMANAGER_HPP
#define CAPSTONE_SDL_SHADERMANAGER_HPP


#include <memory>
#include <gfx/shader.hpp>
#include <gfx/shaderType.hpp>

class ShaderManager
{
	std::unique_ptr<Shader> simpleShader;
	std::unique_ptr<Shader> lightedShader;

public:
	void initShaders();
	
	void cleanupShaders();
	
	Shader * getShader( ShaderType shader );
};


#endif //CAPSTONE_SDL_SHADERMANAGER_HPP
