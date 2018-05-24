#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include "Vec2.h"
#include "Character.h"

class GameData {
public:
	static Vec2 screenSize;
	static Character* player;
	static int nMonsters;
	static int nCivilians;
	static bool playerVictory;
};

#endif /* GAMEDATA_H_ */
