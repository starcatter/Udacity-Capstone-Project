//
// Created by superbob on 2020-06-02.
//

#include <SDL.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>

#include "app.hpp"

#include "managers/displayManager.hpp"
#include "managers/physicsManager.hpp"
#include "managers/modelManager.hpp"
#include "managers/sceneManager.hpp"
#include "managers/shaderManager.hpp"
#include "logic/gameLogic.hpp"

#include <glm/glm.hpp>

static void logOutput(void*           userdata,
					  int             category,
					  SDL_LogPriority priority,
					  const char*     message){
	// TODO: display log on screen
}

int App::Run()
{
	// enable log handler
	// SDL_LogSetOutputFunction(logOutput, nullptr);
	
	/* Enable standard application logging */
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	
	/* Initialize SDL */
	int sdlInit = SDL_Init(SDL_INIT_VIDEO);
	
	if ( sdlInit != 0 )
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
		return 1;
	}
	
	if( display->initGraphics() != 0 ){
		return 1;
	}
	
	models->initModels();
	
	shaders->initShaders();
	
	physics->initWorld();
	
	
	mainLoop();
	
	cleanup();
	
	return 0;
}

void App::mainLoop()
{
	SDL_Event event;
	
	// mouse cursor in 3d space
	glm::vec3 hitPos{0,0,0};
	
	// player's mass
	float mass = logic->getMainBoxMass();
	
	while ( !SDL_QuitRequested())
	{
		auto player = physics->getPlayerPos();
		
		while ( SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
				{
					SDL_KeyboardEvent *kbEvent = reinterpret_cast<SDL_KeyboardEvent *>(&event);
					// press space to jump, hold to float
					if( kbEvent->keysym.sym == SDLK_SPACE ){
						physics->applyForceToPlayer(0, 2*mass, 0);
					}
					// press z to break, or tumble
					if( kbEvent->keysym.sym == SDLK_z ){
						physics->setPlayerFriction(10);
					}
					break;
				}
				case SDL_KEYUP:
				{
					SDL_KeyboardEvent *kbEvent = reinterpret_cast<SDL_KeyboardEvent *>(&event);
					if( kbEvent->keysym.sym == SDLK_z ){
						physics->setPlayerFriction(0.3);
					}
					break;
				}

				case SDL_MOUSEMOTION:
				{
					SDL_MouseMotionEvent *mmEvent = reinterpret_cast<SDL_MouseMotionEvent *>(&event);
					
					hitPos = physics->getMouseClickPosition(mmEvent->x,mmEvent->y,640,480,&scene->getCamera());
					
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					SDL_MouseButtonEvent *mbEvent = reinterpret_cast<SDL_MouseButtonEvent *>(&event);
					if(mbEvent->button == SDL_BUTTON_LEFT)
					{
						action=PlayerAction::pull;
					} else if (mbEvent->button == SDL_BUTTON_RIGHT){
						action=PlayerAction::push;
					}
					break;
				}

				case SDL_MOUSEBUTTONUP:
				{
					SDL_MouseButtonEvent *mbEvent = reinterpret_cast<SDL_MouseButtonEvent *>(&event);
					action=PlayerAction::none;
					break;
				}

				default: break;
			}
		}
		
		// move player cube
		SDL_Keymod mod = SDL_GetModState();
		switch(action){
			case PlayerAction::none:break;
			case PlayerAction::push: physics->applyForceToPlayer(( player.x - hitPos.x ) * (mass/10), 0.2, ( player.z - hitPos.z ) * (mass/10), mod|KMOD_SHIFT); break;
			case PlayerAction::pull: physics->applyForceToPlayer(( hitPos.x - player.x ) * (mass/10), 0.2, ( hitPos.z - player.z ) * (mass/10),mod|KMOD_SHIFT); break;
		}

		// place cursor on top of arena
		scene->setCursorPos(hitPos.x, hitPos.z);
		
		display->render3d();
		
		// simulate physics and update scene data
		scene->update(1000. / 60.);
		
		// update enemy actions
		logic->update();
		
		SDL_Delay(1000 / 60);
	}
}

void App::cleanup()
{
	physics->cleanup();
	models->cleanupModels();
	shaders->cleanupShaders();
	display->cleanup();
	SDL_Quit();
}

App::App():
	physics(std::make_unique<PhysicsManager>()),
	models(std::make_unique<ModelManager>()),
	shaders(std::make_unique<ShaderManager>()),
	scene(std::make_unique<SceneManager>(physics.get())),
	logic(std::make_unique<GameLogic>(scene.get(), physics.get())),
	display(std::make_unique<DisplayManager>(models.get(), shaders.get(), scene.get()))
{}

App::~App()
{
}
