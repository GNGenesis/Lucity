#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"

#include "StageState.h"
#include "BossStageState.h"

#include "Sprite.h"
#include "Text.h"
#include "CameraFollower.h"

#include "StageState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "Sprite.h"
#include "Sound.h"
#include "Text.h"
#include "TileMap.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "MainObject.h"

#include "Player.h"
#include "NPC.h"
#include "Monster.h"

TitleState::TitleState() : State() {
	GameObject* go;



	go = new GameObject();
	TileSet* set = new TileSet(*go, "assets/img/tileSet.png", 64, 64);
	TileMap* map = new TileMap(*go, set, "assets/map/tileMap.txt");
	go->AddComponent(map);
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	NPCList.emplace_back(Personality("girl", 150, 200, 1, 3, 1, 3, { "hobo" }, { "suit", "tree" }));
	NPCList.emplace_back(Personality("hobo", 150, 150, 2, 2, 1, 2, {}, { "suit", "trashcan" }));
	NPCList.emplace_back(Personality("luv", 150, 50, 3, 1, 2, 2, { "old" }, { "girl", "suit" }));
	NPCList.emplace_back(Personality("old", 50, 250, 3, 1, 1.5, 2, {}, { "luv", "bench" }));
	NPCList.emplace_back(Personality("suit", 150, 150, 2, 2, 0.5, 1, {}, {}));

	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);

	for (int i = 0; i < 10; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, NPCList[rand() % NPCList.size()]));
		go->box.SetCenter(rand() % mw, rand() % mh);
		AddObject(go, "MAIN");
	}

		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "bench", 1, Vec2(3, 3), true));
		go->box.SetPos(Vec2(300,200));
		AddObject(go, "MAIN");

	//Trashcan
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "trashcan", 1, Vec2(3, 3), true));
		go->box.SetPos(Vec2(235,200));
		AddObject(go, "MAIN");

	//Tree
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "tree", 1, Vec2(3, 3), true));
		go->box.SetPos(Vec2(600,200));
		AddObject(go, "MAIN");


	//Text
	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/8bit.ttf", 60, "PRESS SPACE TO CONTINUE", SDL_Color{ 26,31,22,43 }, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(512, 500)-(go->box.GetSize()/2)));
	AddObject(go, "GUI");

	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/8bit.ttf", 60, "PRESS F1 TO BOSS FIGHT", SDL_Color{ 26,31,22,43 }, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(512, 400) - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/8bit.ttf", 99, "Lucity", SDL_Color{26,31,22,43}, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(512, 150) - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");
}

TitleState::~TitleState() {

}

void TitleState::LoadAssets() {

}

void TitleState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void TitleState::Pause() {

}

void TitleState::Resume() {

}

void TitleState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	if(InputManager::KeyPress(SPACE_KEY))
		Game::GetInstance().Push(new StageState());

	if (InputManager::KeyPress(F1_KEY))
		Game::GetInstance().Push(new BossStageState());

	UpdateArray(dt, "BG");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	UpdateArray(dt, "GUI");
}

void TitleState::Render() {
	RenderArray("BG");
	RenderArray("MAIN");
	RenderArray("MISC");
	RenderArray("GUI");
}
