//
// Created by superbob on 2020-06-02.
//

#ifndef CAPSTONE_SDL_APP_HPP
#define CAPSTONE_SDL_APP_HPP

#include <memory>

class SDL_Window;
class SDL_Renderer;

class DisplayManager;
class PhysicsManager;
class ModelManager;
class SceneManager;
class ShaderManager;
class GameLogic;

class Enemy;

enum class PlayerAction{
	none,
	push,
	pull
};

class App
{
	std::unique_ptr<PhysicsManager> physics;
	std::unique_ptr<ModelManager> models;
	std::unique_ptr<ShaderManager> shaders;
	std::unique_ptr<SceneManager> scene;
	std::unique_ptr<GameLogic> logic;
	std::unique_ptr<DisplayManager> display;
	
	PlayerAction action{PlayerAction::none};
	
	void mainLoop();
	void cleanup();
	
public:
	App();
	virtual ~App();
	
	int Run();
};


#endif //CAPSTONE_SDL_APP_HPP
