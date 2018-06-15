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
#include "Boss.h"

StageState::StageState() : State() {
	GameObject* go;

	//Background
	/*go = new GameObject();
	go->AddComponent(new Sprite(*go, "assets/img/ocean.jpg"));
	go->AddComponent(new CameraFollower(*go));
	go->box.SetSize(Vec2());
	AddObject(go, "BG");*/

	NPCList.emplace_back(Personality("girl", 100, 200, 1, 2, 1, 2, {"monster"}, {"bench", "tree"}));
	NPCList.emplace_back(Personality("luv", 100, 50, 2, 2, 1.5, 3, {"monster"}, {"bench", "girl"}));
	NPCList.emplace_back(Personality("old", 50, 300, 3, 1, 1, 1, {"monster"}, {"bench"}));
	NPCList.emplace_back(Personality("suit", 50, 150, 2, 1, 1, 2, {"monster"}, {"bench"}));

	monsterList.emplace_back(Personality("girl", 30, 150, 0.1, 5, 0, 1, {"bench"}, {}));
	monsterList.emplace_back(Personality("luv", 150, 150, 20, 2, 0, 2, {"bench"}, {}));
	monsterList.emplace_back(Personality("old", 450, 150, 0.1, 2, 0, 1, {"bench"}, {}));
	monsterList.emplace_back(Personality("suit", 150, 3000, 5, 0.3, 0, 2, {"bench"}, {}));

	//TileMap
	go = new GameObject();
	set = new TileSet(*go, "assets/img/tileSet.png", 64, 64);
	TileMap* map = new TileMap(*go, set, "assets/map/tileMap.txt");
	go->AddComponent(map);
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	int mw = 64*map->GetWidth();
	int mh = 64*map->GetHeight();
	GameData::mapSize = Vec2(mw, mh);

	//Text
	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 72, " ", SDL_Color {}, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
	AddObject(go, "GUI");

	//Bench
	for(int i = 0; i < 4; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "bench", 1, Vec2(3, 3), true, true));
		go->box.SetPos(Vec2(rand()%mw, rand()%mh));
		AddObject(go, "MAIN");
	}

	//Trashcan
	for(int i = 0; i < 4; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "trashcan", 1, Vec2(3, 3), true, true));
		go->box.SetPos(Vec2(rand()%mw, rand()%mh));
		AddObject(go, "MAIN");
	}

	//Tree
	for(int i = 0; i < 4; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "tree", 1, Vec2(3, 3), true));
		go->box.SetPos(Vec2(rand()%mw, rand()%mh));
		AddObject(go, "MAIN");
	}

	//Boss
	go = new GameObject();
	go->AddComponentAsFirst(new Boss(*go, monsterList[3]));
	go->box.SetCenter(rand()%mw, rand()%mh);
	AddObject(go, "MAIN");

	//Players
	for(int i = 3; i >= 0; i--) {
		go = new GameObject();
		go->AddComponentAsFirst(new Player(*go, "lucas", i));
		go->box.SetCenter(mw/2, mh/2);
		AddObject(go, "MAIN");
	}

	Camera::Follow(go);

	backgroundMusic = Music("assets/audio/theme.ogg");
	backgroundMusic.Play();
}

StageState::~StageState() {
	delete set;
}

void StageState::LoadAssets() {

}

void StageState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void StageState::Pause() {

}

void StageState::Resume() {

}

void StageState::CollisionCheck() {
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

void StageState::DeletionCheck() {
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

void StageState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		popRequested = true;

	if(InputManager::KeyPress(SPACE_KEY))
		GameData::debug = !GameData::debug;

	if(objects["GUI"].size() > 0) {
		Text* txt = (Text*)objects["GUI"][0]->GetComponent("Text");
		if(txt) {
			char a[3], b[3];
			sprintf(a, "%d", GameData::nMonsters);
			sprintf(b, "%d", GameData::nCivilians);
			std::string nm = "NM ";
			std::string nc = " NC ";
			std::string text = nm+a+nc+b;
			txt->SetText(text);
		}
	}

	UpdateArray(dt, "BG");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	UpdateArray(dt, "GUI");
	CollisionCheck();
	DeletionCheck();
}

void StageState::Render() {
	RenderArray("BG");
	RenderArray("MAIN");
	RenderArray("MISC");
	RenderArray("GUI");
}
