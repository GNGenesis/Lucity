#include "Game.h"
#include "TitleState.h"

int main(int argv, char** args) {
	Game game = Game::GetInstance();
	State* newState = new TitleState();
	game.Push(newState);
	game.Run();
	printf("Thanks for playing!\n");
	return 0;
}
