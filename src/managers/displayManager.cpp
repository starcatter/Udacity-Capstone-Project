//
// Created by superbob on 2020-06-03.
//

#include "displayManager.hpp"

#include <GL/glew.h>

#include <GL/GL.h>
#include <GL/GLU.h>

#include <SDL_log.h>
#include <SDL_opengl.h>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "managers/modelManager.hpp"
#include "managers/shaderManager.hpp"
#include "managers/sceneManager.hpp"

int DisplayManager::initGraphics()
{
	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	// Create an application window with the following settings:
	window = SDL_CreateWindow("Cube Wrestling",  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			640,                               // width, in pixels
			480,                               // height, in pixels
			SDL_WINDOW_OPENGL              // flags - see below
	);
	
	if ( !window )
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n", SDL_GetError());
		return 1;
	}
	
	//Create context
	sdlGlContext = SDL_GL_CreateContext(window);
	if ( sdlGlContext == NULL )
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return 1;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if ( !renderer )
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer creation for window fail : %s\n", SDL_GetError());
		return 1;
	}
	
	
	if ( !initGl() )
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL init error: %s\n", SDL_GetError());
		return 1;
	}
	
	return 0;
}

void DisplayManager::cleanup()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &VAO);
	
	SDL_DestroyRenderer(renderer);
	SDL_GL_DeleteContext(sdlGlContext);
	SDL_DestroyWindow(window);
}

SDL_Renderer *DisplayManager::getRenderer()
{
	return renderer;
}



// OpenGL init code based on https://lazyfoo.net/tutorials/SDL/50_SDL_and_opengl_2/index.php
bool DisplayManager::initGl(){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) ;
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 ) ;
	
	SDL_GL_SetSwapInterval(0);
	glewExperimental=true;
	GLenum err=glewInit();
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0,0.0,0.0,1.0);
	
	//shader = std::make_unique<Shader>( "simple.vs","simple.fs");
	
	return true;
}

void DisplayManager::render3d(){
	// render
	// ------
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// lighting
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	
	drawObject(scene->getBoard());
	drawObject(scene->getPlayer());
	drawObject(scene->getCursor());
	for( const auto & enemy : scene->getEnemies()){
		if(enemy.enabled){
			drawObject(enemy);
		}
	}
	// drawObject(scene->getTarget());
	
	SDL_GL_SwapWindow(window);
}

void DisplayManager::drawObject( const SceneObject &object ) const
{
	ShaderType shaderType = object.shader;
	auto shader = shaders->getShader(shaderType);
	// activate shader
	shader->use();
	
	const auto & camera = scene->getCamera();
	
	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(75.f), (float)640 / (float)480, 0.1f, 100.0f);
	shader->setMat4("projection", projection);
	
	// camera/view transformation
	glm::mat4 view = camera.GetViewMatrix();
	shader->setMat4("view", view);
	
	const MeshData & meshData = models->getMeshData(object.mesh);
	
	switch(shaderType){
		case ShaderType::simpleColor:
				shader->setVec4("ourColor", object.color);
			break;
		case ShaderType::lightedColor:
			shader->setVec3("objectColor", object.color);
			shader->setVec3("lightColor", {1,1,1});
			shader->setVec3("lightPos", {5,10,5});
			break;
	}
	
	
	glBindVertexArray(meshData.VAO);
	
	shader->setMat4("model", object.getMatrix());
	
	glDrawArrays(GL_TRIANGLES, 0, meshData.vertexCount);
}

DisplayManager::DisplayManager( ModelManager *models,ShaderManager * shaders,SceneManager * scene )
		: models(models),shaders(shaders),scene(scene){}
