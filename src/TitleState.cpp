#include "TitleState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "StageState.h"
#include "BossStageState.h"

#include "Sprite.h"
#include "Sound.h"
#include "Text.h"
#include "TileMap.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "MainObject.h"

#include "NPC.h"
#include "Monster.h"

#include <algorithm>

bool SortRenderOrder_TS(std::shared_ptr<GameObject> i, std::shared_ptr<GameObject> j) { return (i->box.y + i->box.h < j->box.y + j->box.h); }

TitleState::TitleState() : State() {
	GameObject* go;

	NPCList.emplace_back(Personality("girl", 150, 200, 1, 3, 1, 3, {"hobo"}, {"suit", "tree"}));
	NPCList.emplace_back(Personality("hobo", 150, 150, 2, 2, 1, 2, {}, {"suit", "trashcan"}));
	NPCList.emplace_back(Personality("luv", 150, 50, 3, 1, 2, 2, {"old"}, {"girl", "suit"}));
	NPCList.emplace_back(Personality("old", 50, 250, 3, 1, 1.5, 2, {}, {"luv", "bench"}));
	NPCList.emplace_back(Personality("suit", 150, 150, 2, 2, 0.5, 1, {}, {}));

	//TileMap
	go = new GameObject();
	set = new TileSet(*go, "assets/img/tileSet.png", 64, 64);
	TileMap* map = new TileMap(*go, set, "assets/map/tileMap.txt");
	go->AddComponent(map);
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);

	//Text
	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/8bit.ttf", 60, "PRESS SPACE TO CONTINUE", SDL_Color{ 255,255,255,128 }, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(512, 500) - (go->box.GetSize()/2)));
	AddObject(go, "GUI");

	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/8bit.ttf", 60, "PRESS RETURN TO BOSS FIGHT", SDL_Color{ 0,0,0,128 }, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(512, 400) - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/8bit.ttf", 99, "Lucity", SDL_Color{ 255,255,255,128 }, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(512, 150) - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	//Bench
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

	//NPCs
	for (int i = 0; i < 10; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, NPCList[rand()%NPCList.size()]));
		go->box.SetCenter(rand() % mw, rand() % mh);
		AddObject(go, "MAIN");
	}
}

TitleState::~TitleState() {
	delete set;
}

void TitleState::LoadAssets() {

}

void TitleState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void TitleState::Pause() {
	for(int i = objects["MAIN"].size() - 1; i >= 0 ; i--) {
		if(objects["MAIN"][i]->GetComponent("NPC") && !objects["MAIN"][i]->GetComponent("Boss")) {
			if(Camera::GetFocus() == objects["MAIN"][i].get())
				Camera::Unfollow();
			objects["MAIN"].erase(objects["MAIN"].begin() + i);
		}
	}
}

void TitleState::Resume() {
	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	if(GameData::playerVictory) {
		set->SetTileSet("assets/img/tileSet.png");

		//NPCs
		for (int i = 0; i < 10; i++) {
			GameObject*  go = new GameObject();
			go->AddComponentAsFirst(new NPC(*go, NPCList[rand()%NPCList.size()]));
			go->box.SetCenter(rand() % mw, rand() % mh);
			AddObject(go, "MAIN");
		}
	}
	else {
		set->SetTileSet("assets/img/bossTileSet.png");

		//Monsters
		for (int i = 0; i < 10; i++) {
			GameObject* go = new GameObject();
			Monster* mon = new Monster(*go, NPCList[rand()%NPCList.size()]);
			mon->Transform();
			go->AddComponentAsFirst(mon);
			go->box.SetCenter(rand() % mw, rand() % mh);

			AddObject(go, "MAIN");
		}
	}
	if(GameData::bossStageUnlocked) {
		Text* txt = (Text*)objects["GUI"][1]->GetComponent("Text");
		txt->SetColor(SDL_Color { 255,255,255,128 });
	}
}

void TitleState::CollisionCheck() {
	for(unsigned i = 0; i < objects["MAIN"].size(); i++) {
		for(unsigned j = i+1; j < objects["MAIN"].size(); j++) {
			if(objects["MAIN"][i]->IsActive() && objects["MAIN"][j]->IsActive()) {
				Collider* objA = (Collider*) objects["MAIN"][i]->GetComponent("Collider");
				Collider* objB = (Collider*) objects["MAIN"][j]->GetComponent("Collider");
				if(objA && objB) {
					bool collided = false;
					if(objA->GetMode() == Collider::RECT) {
						if(objB->GetMode() == Collider::RECT)
							collided = Collision::IsCollidingRectRect(objA->box, objB->box, objA->rotation, objB->rotation);
						else
							collided = Collision::IsCollidingCircleRect(objB->circle, objA->box, objA->rotation);
					}
					else {
						if(objB->GetMode() == Collider::RECT)
							collided = Collision::IsCollidingCircleRect(objA->circle, objB->box, objB->rotation);
						else
							collided = Collision::IsCollidingCircleCircle(objA->circle, objB->circle);	
					}
					if(collided) {
						objects["MAIN"][i]->NotifyCollision(*objects["MAIN"][j]);
						objects["MAIN"][j]->NotifyCollision(*objects["MAIN"][i]);
					}
				}
			}
		}
	}
}

void TitleState::DeletionCheck() {
	for(auto& i: objects) {
		for(int j = i.second.size()-1; j >= 0; j--) {
			if(i.second[j]->IsDead()) {
				if(Camera::GetFocus() == i.second[j].get())
					Camera::Unfollow();
				i.second.erase(i.second.begin()+j);
			}
		}
	}
}

void TitleState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	if(InputManager::KeyPress(SPACE_KEY))
		Game::GetInstance().Push(new StageState());

	if(GameData::bossStageUnlocked) {
		if(InputManager::KeyPress(SDLK_RETURN))
			Game::GetInstance().Push(new BossStageState());
	}
	else {
		if(InputManager::KeyPress(SDLK_F1))
			Game::GetInstance().Push(new BossStageState());
	}

	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	UpdateArray(dt, "GUI");
	CollisionCheck();
	DeletionCheck();

	std::sort(objects["EFFECT"].begin(), objects["EFFECT"].end(), SortRenderOrder_TS);
	std::sort(objects["MAIN"].begin(), objects["MAIN"].end(), SortRenderOrder_TS);
}

void TitleState::Render() {
	RenderArray("BG");
	RenderArray("EFFECT");
	RenderArray("MAIN");
	RenderArray("MISC");
	RenderArray("GUI");
}
