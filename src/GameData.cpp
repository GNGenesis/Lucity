#include "GameData.h"

bool GameData::debug;

Vec2 GameData::mapSize;
Timer GameData::eventT;
float GameData::eventCD;
int GameData::nMonsters;
int GameData::nCivilians;
bool GameData::paused;
bool GameData::playerVictory;
bool GameData::bossStageUnlocked;
std::weak_ptr<GameObject> GameData::book;
std::weak_ptr<GameObject> GameData::player;

