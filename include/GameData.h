#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include "Vec2.h"
#include "GameObject.h"

#include <memory>

class GameData {
public:
	static bool debug;

	static Vec2 mapSize;
	static int nMonsters;
	static int nCivilians;
	static bool playerVictory;
	static std::weak_ptr<GameObject> player;
};

#endif /* GAMEDATA_H_ */
