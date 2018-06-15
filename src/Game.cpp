#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF

#include "Game.h"
#include "Resources.h"
#include "InputManager.h"
#include "Camera.h"

#include <stdlib.h>
#include <time.h>

Game* Game::instance;
std::stack<std::unique_ptr<State>> Game::stateStack;
State* Game::storedState;

Game::Game(std::string title, int width, int height) {
	if(instance) {
		printf("Multiple Instances\n");
		exit(EXIT_FAILURE);
	}else{
		instance = this;
	}

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK)) {
		printf("SDL_Init failed\n");
		exit(EXIT_FAILURE);
	}

	if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
		printf("IMG_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(!Mix_Init(MIX_INIT_OGG)) {
		printf("Mix_Init failed: %s\n", SDL_GetError());
		//exit(EXIT_FAILURE);
	}

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
		printf("Mix_OpenAudio failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	Mix_AllocateChannels(32);

	if(TTF_Init()) {
		printf("TTF_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//SDL_Rect screen;
	//SDL_GetDisplayBounds(0, &screen);
	Uint32 flags = 0;//SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN;
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);//screen.w, screen.h, flags);
	if(!window) {
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_JoystickEventState(SDL_ENABLE);

	srand(time(NULL));
}

Game::~Game() {
	InputManager::CloseJoysticks();
	if(storedState)
		delete storedState;
	while(!stateStack.empty())
		stateStack.pop();
	Resources::CleanUp();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	printf("We have cleaned it all up now, you can go already.\n");
}

void Game::CalculateDeltaTime() {
	dt = SDL_GetTicks() - frameStart;
	frameStart = frameStart + dt;
}

float Game::GetDeltaTime() {
	return dt/1000;
}

Game& Game::GetInstance() {
	if(!instance)
		new Game("LUCITY UM JOGO MUITO LOUCO", 1024, 600);
	return *instance;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

State& Game::GetCurrentState() {
	return *stateStack.top().get();
}

void Game::Push(State* state) {
	storedState = state;
}

void Game::Run() {
	if(storedState) {
		stateStack.emplace(storedState);
		stateStack.top()->Start();
		storedState = nullptr;
	}
	if(!stateStack.empty()) {
		while(!stateStack.top()->QuitRequested()) {
			InputManager::CloseJoysticks();
			InputManager::LoadJoysticks();
			while(!storedState && !stateStack.top()->PopRequested() && !stateStack.top()->QuitRequested()) {
				if(SDL_RenderClear(renderer))
					printf("SDL_RenderClear failed: %s\n", SDL_GetError());
				CalculateDeltaTime();
				Camera::Update(GetDeltaTime());
				InputManager::Update();
				stateStack.top()->Update(GetDeltaTime());
				stateStack.top()->Render();
				SDL_RenderPresent(renderer);
				SDL_Delay(33);
			}
			if(storedState) {
				stateStack.top()->Pause();
				stateStack.emplace(storedState);
				stateStack.top()->Start();
				storedState = nullptr;
			}
			else if(stateStack.top()->PopRequested()) {
				stateStack.pop();
				Resources::Clear();
				if(!stateStack.empty()) {
					stateStack.top()->Resume();
				}
			}
		}
	}
	printf("Game Over.\n");
}
