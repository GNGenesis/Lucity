#ifndef GAME_H_
#define GAME_H_

#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.h"

#include <string>
#include <stack>
#include <memory>

class Game {
private:
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	static std::stack<std::unique_ptr<State>> stateStack;
	static State* storedState;
	int frameStart;
	float dt;

	Game(std::string title, int width, int height);
	void CalculateDeltaTime();

public:
	~Game();
	float GetDeltaTime();
	static Game& GetInstance();
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	void Push(State* state);
	void Run();
};

#endif /* GAME_H_ */
