#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include "Vec2.h"
#include "Timer.h"
#include "GameObject.h"

#include <memory>

class GameData {
public:
	static bool debug;

	static Vec2 mapSize;
	static Timer eventT;
	static float eventCD;
	static int nMonsters;
	static int nCivilians;
	static bool paused;
	static bool playerVictory;
	static bool bossStageUnlocked;
	static std::weak_ptr<GameObject> book;
	static std::weak_ptr<GameObject> player;
};

#endif /* GAMEDATA_H_ */
