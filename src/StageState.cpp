#include "StageState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "EndState.h"

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
	bg = new GameObject();
	map = new GameObject();
	set = new TileSet(*map, "assets/img/tileSet.png", 64, 64);

	//Background
	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box.SetSize(Vec2());
	bg->Deactivate();

	//TileMap
	map->AddComponent(new TileMap(*map, set, "assets/map/tileMap.txt"));
	map->box.SetSize(Vec2());

	GameObject* go;

	//GIRLRAWR
	go = new GameObject();
	go->AddComponentAsFirst(new Monster(*go, Personality("girl", Vec2(10, 200), 0.1, 5, 0, 1)));
	go->box.SetCenter(320, 320);
	AddObject(go);

	//LUVRAWR
	go = new GameObject();
	go->AddComponentAsFirst(new Monster(*go, Personality("luv", Vec2(150, 150), 22, 2, 0, 2)));
	go->box.SetCenter(320, 320);
	AddObject(go);

	//OLDRAWR
	go = new GameObject();
	go->AddComponentAsFirst(new Monster(*go, Personality("old", Vec2(600, 200), 0.3, 2, 0, 1)));
	go->box.SetCenter(320, 320);
	AddObject(go);

	//SUITRAWR
	go = new GameObject();
	go->AddComponentAsFirst(new Monster(*go, Personality("suit", Vec2(100, 2000), 5, 0.3, 0, 2)));
	go->box.SetCenter(320, 320);
	AddObject(go);

	//GIRL
	for(int i = 0; i < 5; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, Personality("girl", Vec2(100, 200), 1, 2, 0, 2)));
		go->box.SetCenter(320, 320);
		AddObject(go);
	}

	//LUV
		for(int i = 0; i < 5; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, Personality("luv", Vec2(100, 50), 2, 2, 0, 3)));
		go->box.SetCenter(320, 320);
		AddObject(go);
	}

	//OLD
	for(int i = 0; i < 5; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, Personality("old", Vec2(50, 300), 3, 1, 0, 1)));
		go->box.SetCenter(320, 320);
		AddObject(go);
	}

	//SUIT
	for(int i = 0; i < 5; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, Personality("suit", Vec2(50, 150), 2, 1, 0, 2)));
		go->box.SetCenter(320, 320);
		AddObject(go);
	}

	//Player4
	go = new GameObject();
	go->AddComponentAsFirst(new Player(*go, 3));
	go->box.SetCenter(604, 640);
	AddObject(go);

	//Player3
	go = new GameObject();
	go->AddComponentAsFirst(new Player(*go, 2));
	go->box.SetCenter(604, 640);
	AddObject(go);

	//Player2
	go = new GameObject();
	go->AddComponentAsFirst(new Player(*go, 1));
	go->box.SetCenter(604, 640);
	AddObject(go);

	//Player
	go = new GameObject();
	go->AddComponentAsFirst(new Player(*go, 0));
	go->box.SetCenter(704, 640);
	AddObject(go);

	Camera::Follow(go);

	backgroundMusic = Music("assets/audio/theme.ogg");
	backgroundMusic.Play();
}

StageState::~StageState() {
	delete set;
	delete map;
	delete bg;
}

void StageState::LoadAssets() {

}

void StageState::Start() {
	LoadAssets();
	bg->Start();
	map->Start();
	StartArray();
	started = true;
}

void StageState::Pause() {
	for(unsigned i = 0; i < objectArray.size(); i++) {
		Sound* sound = (Sound*) objectArray[i]->GetComponent("Sound");
		if(sound)
			sound->Stop();
	}
}

void StageState::Resume() {
	backgroundMusic.Play();
	objectArray.clear();
}

void StageState::CollisionCheck() {
	for(unsigned i = 0; i < objectArray.size(); i++) {
		for(unsigned j = i+1; j < objectArray.size(); j++) {
			if(objectArray[i]->IsActive() && objectArray[j]->IsActive()) {
				Collider* objA = (Collider*) objectArray[i]->GetComponent("Collider");
				Collider* objB = (Collider*) objectArray[j]->GetComponent("Collider");
				if(objA && objB) {
					if(Collision::IsColliding(objA->box, objB->box, objA->rotation, objB->rotation)) {
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
		}
	}
}

void StageState::DeletionCheck() {
	for(int i = objectArray.size()-1; i >= 0; i--) {
		if(objectArray[i]->IsDead()) {
			if(Camera::GetFocus() == objectArray[i].get())
				Camera::Unfollow();
			objectArray.erase(objectArray.begin()+i);
		}
	}
}

void StageState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		popRequested = true;

	bg->Update(dt);
	map->Update(dt);
	UpdateArray(dt);
	CollisionCheck();
	DeletionCheck();
}

void StageState::Render() {
	TileMap* tileMap = (TileMap*) map->GetComponent("TileMap");
	
	bg->Render();
	tileMap->RenderLayer(0, Camera::pos.x, Camera::pos.y);
	RenderArray();
	tileMap->RenderLayer(1, Camera::pos.x*1.5, Camera::pos.y*1.5);
}
