#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#define INCLUDE_SDL
#include "SDL_include.h"

#include "Vec2.h"
#include "Timer.h"
#include "GameObject.h"

#include <memory>

class GameData {
public:
	static bool debug;
	static bool popAgain;

	static SDL_Window* window;
	static Vec2 globalScale;
	static Vec2 mapSize;
	static Timer eventT;
	static float eventCD;
	static int nMonsters;
	static int nCivilians;
	static bool paused;
	static bool playerVictory;
	static bool bossStageUnlocked;
	static bool fullscreen;
	static std::weak_ptr<GameObject> book;
	static std::weak_ptr<GameObject> player;

	static int upperLimit;
	static int key;
	static int UP_MOV;
	static int DOWN_MOV;
	static int LEFT_MOV;
	static int RIGHT_MOV;
	static int MAGIC_BUBBLES;
	static int MAGIC_FIREBALL;
	static int MAGIC_CAPTURE;
	static int PAUSE;
};

#endif /* GAMEDATA_H_ */
