#include "GameData.h"

bool GameData::debug;

Vec2 GameData::mapSize;
int GameData::nMonsters;
int GameData::nCivilians;
bool GameData::playerVictory;
std::weak_ptr<GameObject> GameData::player;

