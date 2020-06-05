//
// Created by superbob on 2020-06-03.
//

#ifndef CAPSTONE_SDL_DISPLAYMANAGER_HPP
#define CAPSTONE_SDL_DISPLAYMANAGER_HPP


#include <memory>

#include <SDL_video.h>
#include <SDL_render.h>

#include <glm/glm.hpp>

#include "gfx/shader.hpp"
#include "scene/camera.hpp"
#include "scene/sceneObject.hpp"

class ModelManager;
class ShaderManager;
class SceneManager;

class DisplayManager
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_GLContext sdlGlContext;
	
	//std::unique_ptr<Shader> shader;
	
	ModelManager * models;
	ShaderManager * shaders;
	SceneManager * scene;
	
	bool initGl();
public:
	DisplayManager( ModelManager *models, ShaderManager * shaders, SceneManager * scene );
	
	int initGraphics();
	void cleanup();
	void render3d();
	
	SDL_Renderer *getRenderer();
	
	void drawObject( const SceneObject &object ) const;
};


#endif //CAPSTONE_SDL_DISPLAYMANAGER_HPP
