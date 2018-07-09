#include "BossStageState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "PauseState.h"
#include "EndState.h"

#include "Sprite.h"
#include "Text.h"
#include "HUD.h"
#include "TileMap.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "MainObject.h"

#include "Player.h"
#include "NPC.h"
#include "Boss.h"
#include "Animator.h"

#include <algorithm>

bool SortRenderOrder_BS(std::shared_ptr<GameObject> i, std::shared_ptr<GameObject> j) {
	return (i->box.y < j->box.y);
}

BossStageState::BossStageState() : State() {
	gameOver = false;

	GameData::popAgain = false;

	GameObject* go;

	NPCList.emplace_back(Personality("girl", 150, 200, 1, 3, 1, 3, {"hobo"}, {"suit", "tree"}));
	NPCList.emplace_back(Personality("hobo", 150, 150, 2, 2, 1, 2, {}, {"suit", "trashcan"}));
	NPCList.emplace_back(Personality("luv", 150, 50, 3, 1, 2, 2, {"old"}, {"girl", "suit"}));
	NPCList.emplace_back(Personality("old", 50, 250, 3, 1, 1.5, 2, {}, {"luv", "bench"}));
	NPCList.emplace_back(Personality("suit", 150, 150, 2, 2, 0.5, 1, {}, {}));

	monsterList.emplace_back(Personality("girl", 50, 200, 0.3, 5, 1, 1, {"luv"}, {"hobo"}));
	monsterList.emplace_back(Personality("hobo", 250, 50, 1, 3, 3, 1, {}, {"girl", "luv", "old", "suit"}));
	monsterList.emplace_back(Personality("luv", 150, 150, 10, 2, 1, 2, {}, {"old", "tree"}));
	monsterList.emplace_back(Personality("old", 300, 250, 1, 2, 2, 2, {"tree"}, {"trashcan"}));
	monsterList.emplace_back(Personality("suit", 150, 4000, 5, 0.3, 5, 1, {"bench"}, {}));

	//TileMap
	go = new GameObject();
	set = new TileSet(*go, "assets/img/tileSet.png", 64, 64);
	TileMap* map = new TileMap(*go, set, "assets/map/bossTileMap.txt");
	go->AddComponent(map);
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	int mw = 64*map->GetWidth();
	int mh = 64*map->GetHeight();
	GameData::mapSize = Vec2(mw, mh);
	GameData::upperLimit = 0;

	//Event Countdown
	GameData::eventCD = 30;

	//HUD
	go = new GameObject();
	go->AddComponent(new HUD(*go));
	go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
	AddObject(go, "GUI");
	
	if(true) {
		//Fountain
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "fountain", 1, Vec2(3, 3), true, true));
		go->box.SetCenter(Vec2(mw/2, mh/2));
		AddObject(go, "MAIN");

		//Bench
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "bench", 1, Vec2(3, 3), true, true));
		go->box.SetCenter(Vec2(mw/2, 288));
		AddObject(go, "MAIN");

		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "bench", 1, Vec2(3, 3), true, true));
		go->box.SetCenter(Vec2(mw/2, 736));
		AddObject(go, "MAIN");

		//Trashcan
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "trashcan", 1, Vec2(3, 3), true, true));
		go->box.SetCenter(Vec2(800, 352));
		AddObject(go, "MAIN");

		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "trashcan", 1, Vec2(3, 3), true, true));
		go->box.SetCenter(Vec2(480, 608));
		AddObject(go, "MAIN");

		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "trashcan", 1, Vec2(3, 3), true, true));
		go->box.SetCenter(Vec2(224, 800));
		AddObject(go, "MAIN");

		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "trashcan", 1, Vec2(3, 3), true, true));
		go->box.SetCenter(Vec2(1050, 160));
		AddObject(go, "MAIN");

		//Tree
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "tree", 1, Vec2(3, 3), true));
		go->box.SetCenter(Vec2(352, 224));
		AddObject(go, "MAIN");

		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "tree", 1, Vec2(3, 3), true));
		go->box.SetCenter(Vec2(224, 352));
		AddObject(go, "MAIN");

		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "tree", 1, Vec2(3, 3), true));
		go->box.SetCenter(Vec2(1056, 608));
		AddObject(go, "MAIN");

		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "tree", 1, Vec2(3, 3), true));
		go->box.SetCenter(Vec2(928, 736));
		AddObject(go, "MAIN");
	}

	//Boss
	go = new GameObject();
	boss = new Boss(*go, monsterList[rand()%monsterList.size()]);
	go->AddComponentAsFirst(boss);
	go->box.SetCenter(rand()%mw, rand()%mh);
	AddObject(go, "MAIN");

	GameData::nMonsters++;
	GameData::nMaxMonsters = GameData::nMonsters;

	//NPCs
	for(int i = 0; i < 30; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPC(*go, NPCList[rand()%NPCList.size()]));
		go->box.SetCenter(rand()%mw, rand()%mh);
		AddObject(go, "MAIN");

		GameData::nCivilians++;
	}

	//Players
	go = new GameObject();
	go->AddComponentAsFirst(new Player(*go, "lucas", 0));
	go->box.SetCenter(mw/2, mh/2);
	AddObject(go, "MAIN");

	Camera::Follow(go);

	flipped = false;

	backgroundMusic = Music("assets/audio/theme.ogg");
	backgroundMusic.Play();
}

BossStageState::~BossStageState() {
	GameData::mapSize = Vec2();
	GameData::nMonsters = 0;
	GameData::nCivilians = 0;
	GameData::player = std::weak_ptr<GameObject>();
	delete set;
}

void BossStageState::LoadAssets() {

}

void BossStageState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void BossStageState::Pause() {
	Camera::Unfollow();
	backgroundMusic.Stop();
}

void BossStageState::Resume() {
	GameData::popAgain = false;

	if(!GameData::player.expired())
		Camera::Follow(GameData::player.lock().get());

	backgroundMusic.Play();
}

void BossStageState::Ramble() {
	for(unsigned i = 0; i < objects["MAIN"].size(); i++) {
		if(objects["MAIN"][i]->IsActive() && objects["MAIN"][i]->GetComponent("NPC")) {
			objects["MAIN"][i]->box.SetCenter(rand()%(int)GameData::mapSize.x, rand()%(int)GameData::mapSize.y);
			if(objects["MAIN"][i]->GetComponent("Boss")) {
				NPC* objNPC = (NPC*) objects["MAIN"][i]->GetComponent("NPC");
				objNPC->SetPerson(monsterList[rand()%monsterList.size()]);
			}
		}
	}

	rambleT.Restart();
}

void BossStageState::Flip() {
	if(!flipped) {
		set->SetTileSet("assets/img/bossTileSet.png");
		backgroundMusic.Open("assets/audio/bossTheme.ogg");
		backgroundMusic.Play();
		if(!boss->IsTransformed())
			boss->Transform();
		for(int i = objects["MAIN"].size() - 1; i >= 0 ; i--) {
			if(objects["MAIN"][i]->GetComponent("NPC") && !objects["MAIN"][i]->GetComponent("Boss")) {
				if(Camera::GetFocus() == objects["MAIN"][i].get())
					Camera::Unfollow();
				objects["MAIN"].erase(objects["MAIN"].begin() + i);
			}
			else if(objects["MAIN"][i]->GetComponent("MainObject")) {
				MainObject* mo = (MainObject*) objects["MAIN"][i]->GetComponent("MainObject");
				if(mo->GetName() == "tree") {
					Vec2 pos = objects["MAIN"][i]->box.GetPos();
					objects["MAIN"][i]->RequestDelete();

					GameObject* go = new GameObject();
					go->AddComponentAsFirst(new MainObject(*go, "deadtree", 1, Vec2(3, 3), true));
					go->box.SetPos(pos);
					AddObject(go, "MAIN");
				}
				else {
					mo->Damage(1);				
				}
			}
		}
		flipped = true;
	}
}

void BossStageState::Clear() {
	GameData::nCivilians = 0;
	Flip();
}

void BossStageState::CollisionCheck() {
	for (unsigned i = 0; i < objects["MAIN"].size(); i++) {
		for (unsigned j = i + 1; j < objects["MAIN"].size(); j++) {
			if (objects["MAIN"][i]->IsActive() && objects["MAIN"][j]->IsActive()) {
				Collider* objA = (Collider*)objects["MAIN"][i]->GetComponent("Collider");
				Collider* objB = (Collider*)objects["MAIN"][j]->GetComponent("Collider");
				if (objA && objB) {
					bool collided = false;
					if (objA->GetMode() == Collider::RECT) {
						if (objB->GetMode() == Collider::RECT)
							collided = Collision::IsCollidingRectRect(objA->box, objB->box, objA->rotation, objB->rotation);
						else
							collided = Collision::IsCollidingCircleRect(objB->circle, objA->box, objA->rotation);
					}
					else {
						if (objB->GetMode() == Collider::RECT)
							collided = Collision::IsCollidingCircleRect(objA->circle, objB->box, objB->rotation);
						else
							collided = Collision::IsCollidingCircleCircle(objA->circle, objB->circle);
					}
					if (collided) {
						objects["MAIN"][i]->NotifyCollision(*objects["MAIN"][j]);
						objects["MAIN"][j]->NotifyCollision(*objects["MAIN"][i]);
					}
				}
			}
		}
	}
}

void BossStageState::DeletionCheck() {
	for(auto& i : objects) {
		for(int j = i.second.size() - 1; j >= 0; j--) {
			if(i.second[j]->IsDead()) {
				if(Camera::GetFocus() == i.second[j].get())
					Camera::Unfollow();
				if(i.second[j]->GetComponent("Soul"))
					GameData::nMonsters--;
				else if(i.second[j]->GetComponent("NPC"))
					GameData::nCivilians--;
				i.second.erase(i.second.begin() + j);
			}
		}
	}
}

void BossStageState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		Game::GetInstance().Push(new PauseState());

	if(InputManager::KeyPress(SDLK_F1))
		GameData::debug = !GameData::debug;

	if(InputManager::KeyPress(SDLK_F2))
		GameData::paused = !GameData::paused;

	if(InputManager::KeyPress(SDLK_F5)) {
		gameOver = true;
		GameData::playerVictory = false;
	}

	if(InputManager::KeyPress(SDLK_F6)) {
		gameOver = true;
		GameData::playerVictory = true;
	}

	if(InputManager::KeyPress(SDLK_F7)) {
		GameObject* go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, "tree", 1, Vec2(3, 3), true));
		go->box.SetCenter(InputManager::GetMousePos());
		AddObject(go, "MAIN");
		printf("%.f - %.f\n", InputManager::GetMousePos().x, InputManager::GetMousePos().y);
	}

	if(!gameOver) {
		if(InputManager::KeyPress(SDLK_F3))
			Flip();

		if(InputManager::KeyPress(SDLK_F4))
			Clear();
		
		rambleT.Update(dt);
		if(boss->Ramble())
			Ramble();
		if(!flipped)	
			if(boss->IsTransformed() || GameData::nCivilians == 0)
				Flip();

		if(!flipped)
			GameData::eventT.Update(dt);
		if(GameData::eventT.Get() > GameData::eventCD) {
			for(unsigned int i = 0; i < objects["MAIN"].size(); i++) {
				if(objects["MAIN"][i]->GetComponent("NPC") && !objects["MAIN"][i]->GetComponent("Boss")) {
					objects["MAIN"][i]->RequestDelete();
					GameData::eventT.Restart();
					break;
				}
			}
		}

		if(GameData::nMonsters == 0) {
			gameOver = true;
			GameData::playerVictory = true;
		}
		else if(GameData::player.expired()) {
			gameOver = true;
			GameData::playerVictory = false;
		}
	}
	else {
		Game::GetInstance().Push(new EndState());
	}

	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	UpdateArray(dt, "GUI");
	CollisionCheck();
	DeletionCheck();

	std::sort(objects["EFFECT"].begin(), objects["EFFECT"].end(), SortRenderOrder_BS);
	std::sort(objects["MAIN"].begin(), objects["MAIN"].end(), SortRenderOrder_BS);
}

void BossStageState::Render() {
	if(rambleT.Get() > 0.5) {
		RenderArray("BG");
		RenderArray("EFFECT");
		RenderArray("MAIN");
		RenderArray("MISC");
		RenderArray("GUI");
	}
}
