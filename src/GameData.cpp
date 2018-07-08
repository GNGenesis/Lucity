#include "GameData.h"

bool GameData::debug;
bool GameData::popAgain;

Vec2 GameData::mapSize;
Vec2 GameData::globalScale;
Timer GameData::eventT;
float GameData::eventCD;
int GameData::nMonsters;
int GameData::nCivilians;
bool GameData::paused;
bool GameData::playerVictory;
bool GameData::bossStageUnlocked;
bool GameData::fullscreen;
std::weak_ptr<GameObject> GameData::book;
std::weak_ptr<GameObject> GameData::player;
SDL_Window* GameData::window;

int GameData::key;
int GameData::UP_MOV;
int GameData::DOWN_MOV;
int GameData::LEFT_MOV;
int GameData::RIGHT_MOV;
int GameData::MAGIC_BUBBLES;
int GameData::MAGIC_FIREBALL;
int GameData::MAGIC_CAPTURE;
int GameData::PAUSE;
