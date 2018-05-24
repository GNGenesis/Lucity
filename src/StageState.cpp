#include "StageState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "Personality.h"

#include "Sprite.h"
#include "Sound.h"
#include "Text.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "TileMap.h"

#include "Player.h"
#include "NPC.h"
#include "Monster.h"

StageState::StageState() : State() {
	GameObject* go;
	int sw = GameData::screenSize.x;
	int sh = GameData::screenSize.y;

	//Background
	go = new GameObject();
	go->AddComponent(new Sprite(*go, "assets/img/ocean.jpg"));
	go->AddComponent(new CameraFollower(*go));
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	//TileMap
	go = new GameObject();
	set = new TileSet(*go, "assets/img/tileSet.png", 64, 64);
	go->AddComponent(new TileMap(*go, set, "assets/map/tileMap.txt"));
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	//Text
	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 72, " ", SDL_Color {}, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
	AddObject(go, "GUI");

	//GIRLRAWR
	go = new GameObject();
	go->AddComponentAsFirst(new Monster(*go, Personality("girl", Vec2(30, 150), 0.1, 5, 0, 1)));
	go->box.SetCenter(rand()%sw, rand()%sh);
	AddObject(go, "MAIN");

	//LUVRAWR
	go = new GameObject();
	go->AddComponentAsFirst(new Monster(*go, Personality("luv", Vec2(150, 150), 20, 2, 0, 2)));
	go->box.SetCenter(rand()%sw, rand()%sh);
	AddObject(go, "MAIN");

	//OLDRAWR
	go = new GameObject();
	go->AddComponentAsFirst(new Monster(*go, Personality("old", Vec2(450, 150), 0.3, 2, 0, 1)));
	go->box.SetCenter(rand()%sw, rand()%sh);
	AddObject(go, "MAIN");

	//SUITRAWR
	go = new GameObject();
	go->AddComponentAsFirst(new Monster(*go, Personality("suit", Vec2(150, 3000), 5, 0.3, 0, 2)));
	go->box.SetCenter(rand()%sw, rand()%sh);
	AddObject(go, "MAIN");

	//GIRL
	for(int i = 0; i < 5; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, Personality("girl", Vec2(100, 200), 1, 2, 0, 2)));
		go->box.SetCenter(rand()%sw, rand()%sh);
		AddObject(go, "MAIN");
	}

	//LUV
	for(int i = 0; i < 5; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, Personality("luv", Vec2(100, 50), 2, 2, 0, 3)));
		go->box.SetCenter(rand()%sw, rand()%sh);
		AddObject(go, "MAIN");
	}

	//OLD
	for(int i = 0; i < 5; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, Personality("old", Vec2(50, 300), 3, 1, 0, 1)));
		go->box.SetCenter(rand()%sw, rand()%sh);
		AddObject(go, "MAIN");
	}

	//SUIT
	for(int i = 0; i < 5; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, Personality("suit", Vec2(50, 150), 2, 1, 0, 2)));
		go->box.SetCenter(rand()%sw, rand()%sh);
		AddObject(go, "MAIN");
	}

	//Players
	for(int i = 0; i < 4; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new Player(*go, "lucas", i));
		go->box.SetCenter(680, 384);
		AddObject(go, "MAIN");
	}

	//Camera::Follow(go);

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
					if(Collision::IsColliding(objA->box, objB->box, objA->rotation, objB->rotation)) {
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
	UpdateArray(dt, "GUI");
	CollisionCheck();
	DeletionCheck();
}

void StageState::Render() {
	RenderArray("BG");
	RenderArray("MAIN");
	RenderArray("GUI");
}
