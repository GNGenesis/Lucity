#include "TutorialStageState.h"
#include "StageState.h"
#include "PauseState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "DialogBox.h"
#include "Sprite.h"
#include "Sound.h"
#include "Text.h"
#include "HUD.h"
#include "TileMap.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "MainObject.h"

#include "Player.h"
#include "NPCTutorial.h"
#include "MonsterTutorial.h"

#include <algorithm>

bool SortRenderOrderTutorial_MS(std::shared_ptr<GameObject> i, std::shared_ptr<GameObject> j) {
	return (i->box.y < j->box.y);
}

TutorialStageState::TutorialStageState() : State() {
	tutorialScene = 0;
	gameOver = false;
	GameData::eventCD = 5;
	hudChecked = false;

	GameObject* go;

	NPCList.emplace_back(Personality("girl", 150, 200, 1, 3, 1, 3, { "hobo" }, { "suit", "tree" }));
	NPCList.emplace_back(Personality("hobo", 150, 150, 2, 2, 1, 2, {}, { "suit", "trashcan" }));
	NPCList.emplace_back(Personality("luv", 150, 50, 3, 1, 2, 2, { "old" }, { "girl", "suit" }));
	NPCList.emplace_back(Personality("old", 50, 250, 3, 1, 1.5, 2, {}, { "luv", "bench" }));
	NPCList.emplace_back(Personality("suit", 150, 150, 2, 2, 0.5, 1, {}, {}));

	monsterList.emplace_back(Personality("girl", 50, 200, 0.3, 5, 1, 1, { "luv" }, { "hobo" }));
	monsterList.emplace_back(Personality("hobo", 250, 50, 1, 3, 3, 1, {}, { "girl", "luv", "old", "suit" }));
	monsterList.emplace_back(Personality("luv", 150, 150, 10, 2, 1, 2, {}, { "old", "tree" }));
	monsterList.emplace_back(Personality("old", 300, 250, 1, 2, 2, 2, { "tree" }, { "trashcan" }));
	monsterList.emplace_back(Personality("suit", 150, 4000, 5, 0.3, 5, 1, { "bench" }, {}));

	//TileMap
	go = new GameObject();
	set = new TileSet(*go, "assets/img/cenario/biblioteca/tilesbiblioteca.png", 64, 64);
	TileMap* map = new TileMap(*go, set, "assets/map/tileMapBiblioteca.txt");
	go->AddComponent(map);
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	int mw = 64 * map->GetWidth();
	int mh = 64 * map->GetHeight();
	GameData::mapSize = Vec2(mw, mh);
	GameData::upperLimit = 100;

	//Event Countdown
	GameData::eventCD = 60;
	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 72, "00.0 ", SDL_Color{}, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(1024 - go->box.w, 200)));
	AddObject(go, "GUI");

	//prateleira_full
	go = new GameObject();
	go->AddComponentAsFirst(new Sprite(*go, "assets/img/objects/prateleira_full.png"));
	go->box.SetPos(Vec2(0, 32));
	AddObject(go, "MAIN");
	std::string path;
	int pos = 220;
	for (int i = 0; i <= 4; i++) {
		path = "prateleira" + std::to_string((rand() % 13));
		//prateleira
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, path, 1, Vec2(1, 1), true, false));
		go->box.SetPos(Vec2(78, pos));
		AddObject(go, "MAIN");
		pos += 124;

	}
	pos = 220;
	for (int i = 0; i <= 4; i++) {
		path = "prateleira" + std::to_string((rand() % 13));
		//prateleira
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, path, 1, Vec2(1, 1), true, false));
		go->box.SetPos(Vec2(232, pos));
		AddObject(go, "MAIN");
		pos += 124;

	}

	pos = 220;
	for (int i = 0; i <= 4; i++) {
		path = "prateleira" + std::to_string((rand() % 13));
		//prateleira
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, path, 1, Vec2(1, 1), true, false));
		go->box.SetPos(Vec2(780, pos));
		AddObject(go, "MAIN");
		pos += 124;

	}

	pos = 220;
	for (int i = 0; i <= 4; i++) {
		path = "prateleira" + std::to_string((rand() % 13));
		//prateleira
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, path, 1, Vec2(1, 1), true, false));
		go->box.SetPos(Vec2(936, pos));
		AddObject(go, "MAIN");
		pos += 124;

	}
	//NPCs
	for (int i = 0; i < 10; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new NPCTutorial(*go, NPCList[rand() % NPCList.size()]));
		go->box.SetCenter(rand() % mw, rand() % mh);
		AddObject(go, "MAIN");

		GameData::nCivilians++;
	}
	//Monsters
	for (int i = 0; i < 2; i++) {
		go = new GameObject();
		go->AddComponentAsFirst(new MonsterTutorial(*go, monsterList[rand() % monsterList.size()]));
		go->box.SetCenter(rand() % mw, rand() % mh);
		AddObject(go, "MAIN");

		GameData::nMonsters++;
	}

	// Librarian
	go = new GameObject();
	go->AddComponentAsFirst(new MonsterTutorial(*go, Personality("blib", 300, 250, 1, 2, 2, 2, {}, {})));
	go->box.SetCenter(mw/2, mh/2);
	AddObject(go, "MAIN");
	GameData::nMonsters++;

	//Players
	for (int i = 0; i >= 0; i--) {
		go = new GameObject();
		go->AddComponentAsFirst(new Player(*go, "lucas", 1));
		go->box.SetCenter(mw / 2, mh / 2);
		AddObject(go, "MAIN");
	}

	//Event Countdown
	go = new GameObject();
	go->AddComponent(new DialogBox(*go, "assets/img/HUD/dialog1.png", "assets/font/Sabo-Filled.ttf", "TESTE DE TEXTO NA CAIXA PORRA",Vec2(512,300)));
	AddObject(go, "MISC");

	Camera::Follow(go);

	backgroundMusic = Music("assets/audio/theme.ogg");
	//backgroundMusic.Play();
}

TutorialStageState::~TutorialStageState() {
	GameData::mapSize = Vec2();
	GameData::nMonsters = 0;
	GameData::nCivilians = 0;
	GameData::player = std::weak_ptr<GameObject>();
	delete set;
}

void TutorialStageState::LoadAssets() {

}

void TutorialStageState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void TutorialStageState::Pause() {
	for (int i = objects["MAIN"].size() - 1; i >= 0; i--) {
		if (objects["MAIN"][i]->GetComponent("NPC") && !objects["MAIN"][i]->GetComponent("Boss")) {
			if (Camera::GetFocus() == objects["MAIN"][i].get())
				Camera::Unfollow();
			//objects["MAIN"].erase(objects["MAIN"].begin() + i);
		}
	}
}

void TutorialStageState::Resume() {

}

void TutorialStageState::CollisionCheck() {
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

void TutorialStageState::DeletionCheck() {
	for (auto& i : objects) {
		for (int j = i.second.size() - 1; j >= 0; j--) {
			if (i.second[j]->IsDead()) {
				if (Camera::GetFocus() == i.second[j].get())
					Camera::Unfollow();

				if (i.second[j]->GetComponent("Monster")) {
					GameData::nMonsters--;
					GameData::eventT.Restart();
				}
				else if (i.second[j]->GetComponent("NPC")) {
					GameData::nCivilians--;
				}
				i.second.erase(i.second.begin() + j);
			}
		}
	}
}

void TutorialStageState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY)) {
		popRequested = true;
		GameData::playerVictory = true;
	}

	if(InputManager::KeyPress(SDLK_F1))
		GameData::debug = !GameData::debug;

	if(InputManager::KeyPress(SDLK_F2))
		GameData::paused = !GameData::paused;

	if (hudChecked == false) {
		for (unsigned i = 0; i < objects["GUI"].size(); i++) {
			objects["GUI"][i]->Deactivate();
		}
		hudChecked = true;
	}

	if(GameData::nMonsters == 0) {
		gameOver = true;
		GameData::playerVictory = true;

		//GameOver message
		GameObject* go = new GameObject();
		go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 48, "Well done kiddo, you got them all!", SDL_Color {}, Text::SOLID));
		go->AddComponent(new CameraFollower(*go, Vec2(512-go->box.w/2, 300-go->box.h/2)));
		AddObject(go, "GUI");

		go = new GameObject();
		go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 48, "Press Return to play again!", SDL_Color {}, Text::SOLID));
		go->AddComponent(new CameraFollower(*go, Vec2(512-go->box.w/2, 360-go->box.h/2)));
		AddObject(go, "GUI");
	}
	else if(GameData::player.expired()) {
		gameOver = true;
		GameData::playerVictory = false;

		//GameOver message
		GameObject* go = new GameObject();
		go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 48, "You are a fucking failure...", SDL_Color {}, Text::SOLID));
		go->AddComponent(new CameraFollower(*go, Vec2(512-go->box.w/2, 300-go->box.h/2)));
		AddObject(go, "GUI");

		go = new GameObject();
		go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 48, "Press Return to play again!", SDL_Color {}, Text::SOLID));
		go->AddComponent(new CameraFollower(*go, Vec2(512-go->box.w/2, 360-go->box.h/2)));
		AddObject(go, "GUI");
	}
	else {
		if(InputManager::KeyPress(SDLK_RETURN))
			popRequested = true;
	}

	if (!gameOver) {
		if (!GameData::paused) {
			GameData::eventT.Update(dt);
		}
		switch (tutorialScene) {
		 case 0:
				LibrarianTutorialUpdate(dt);
				break;
			case 1:
				SecondMonsterTutorialUpdate(dt);
				break;
			case 2:
				FreeTutorialUpdate(dt);
				break;
		}
	}

	std::sort(objects["EFFECT"].begin(), objects["EFFECT"].end(), SortRenderOrderTutorial_MS);
	std::sort(objects["MAIN"].begin(), objects["MAIN"].end(), SortRenderOrderTutorial_MS);
}

void TutorialStageState::LibrarianTutorialUpdate(float dt) {

	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	CollisionCheck();
	DeletionCheck();
	if (GameData::eventT.Get() > GameData::eventCD) {
		GameData::eventT.Restart();
		tutorialScene++;
	}

}

void TutorialStageState::SecondMonsterTutorialUpdate(float dt) {

	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	CollisionCheck();
	DeletionCheck();
	if (GameData::eventT.Get() > GameData::eventCD) {
		for (unsigned i = 0; i < objects["GUI"].size(); i++) {
			objects["GUI"][i]->Activate();
		}
		GameData::eventT.Restart();
		tutorialScene++;
	}

}

void TutorialStageState::FreeTutorialUpdate(float dt) {

	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	UpdateArray(dt, "GUI");
	CollisionCheck();
	DeletionCheck();
	if (GameData::eventT.Get() > GameData::eventCD) {
		for (unsigned i = 0; i < objects["GUI"].size(); i++) {
			objects["GUI"][i]->Deactivate();
		}
		GameData::eventT.Restart();
		tutorialScene = 0;
	}

}

void TutorialStageState::Render() {
	RenderArray("BG");
	RenderArray("EFFECT");
	RenderArray("MAIN");
	RenderArray("MISC");
	RenderArray("GUI");
}
