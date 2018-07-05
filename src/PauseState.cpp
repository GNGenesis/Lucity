#include "PauseState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "StageState.h"
#include "TitleState.h"
#include "BossStageState.h"
#include "SettingState.h"

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


PauseState::PauseState() : State() {
	GameObject* go;
	GameObject* goSelectorF;
	GameObject* goSelectorB;
	Sprite * novo;


	//MenuSelector

	/*goSelector = new GameObject();
	goSelector->AddComponent(new Sprite(*goBook, "assets/img/bookM.png"));*/

	//MenuSelector
	goSelectorF = new GameObject();
	Sprite* selector = new Sprite(*goSelectorF, "assets/img/Title/SelectorF.png", 1, 0.01, false, 0.0);
	selector->SetScale(Vec2(3, 3)*GameData::globalScale);
	goSelectorF->AddComponent(selector);

	goSelectorB = new GameObject();
	selector = new Sprite(*goSelectorB, "assets/img/Title/SelectorB.png", 1, 0.01, false, 0.0);
	selector->SetScale(Vec2(3, 3)*GameData::globalScale);
	goSelectorB->AddComponent(selector);

	//MenuBook
	go = new GameObject();
	book = new Sprite(*go, "assets/img/Title/ABRINDO.png", 5, 0.15, false, 0.0);
	book->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
	go->AddComponent(book);
	AddObject(go, "EFFECT");


	//Text
	//NewGame
	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/ResumeButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 180)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "Return",Vec2(300, 300) - (go->box.GetSize() / 2), goSelectorF,goSelectorB, go, true, 0 });

	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/MenuButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 280)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "MainMenu",Vec2(300, 350) - (go->box.GetSize() / 2),goSelectorF,goSelectorB, go, true, 0 });

	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/ExitButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 380)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "Exit",Vec2(300, 400) - (go->box.GetSize() / 2),goSelectorF,goSelectorB, go, true, 0 });
}

PauseState::~PauseState() {

}

void PauseState::LoadAssets() {

}

void PauseState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void PauseState::Pause() {
	for (int i = objects["MAIN"].size() - 1; i >= 0; i--) {
		if (objects["MAIN"][i]->GetComponent("NPC") && !objects["MAIN"][i]->GetComponent("Boss")) {
			if (Camera::GetFocus() == objects["MAIN"][i].get())
				Camera::Unfollow();
			objects["MAIN"].erase(objects["MAIN"].begin() + i);
		}
	}
}

void PauseState::Resume() {

}

void PauseState::DeletionCheck() {
	for (auto& i : objects) {
		for (int j = i.second.size() - 1; j >= 0; j--) {
			if (i.second[j]->IsDead()) {
				if (Camera::GetFocus() == i.second[j].get())
					Camera::Unfollow();
				i.second.erase(i.second.begin() + j);
			}
		}
	}
}

void PauseState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();

	if (InputManager::KeyPress(SDLK_UP)) {
		SetOption(-1);
	}
	if (InputManager::KeyPress(SDLK_DOWN)) {
		SetOption(1);
	}
	if (InputManager::KeyPress(SDLK_KP_ENTER) || InputManager::KeyPress(SDLK_RETURN)) {

		// Check if the event was "NewGame".
		if (SelectedOptionIs("Return")) {
			popRequested = true;
			GameData::paused = !GameData::paused;
		}
		// Check if the event was "BossFight".
		else if (SelectedOptionIs("MainMenu")) {
			Game::GetInstance().Push(new TitleState());
		}
		// Check if the event was "Exit".
		else if (SelectedOptionIs("Exit")) {
			quitRequested = true; // Set to truth the variable that is responsible to validate the quit request of the game.
		}
	}

	if (InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	frameCounter = book->GetFrame();
	if (frameCounter >= 4) {
		UpdateArray(dt, "MAIN");
		UpdateArray(dt, "MISC");
		UpdateArray(dt, "GUI");
		DeletionCheck();
	}

}

void PauseState::Render() {
	RenderArray("BG");
	RenderArray("EFFECT");
	frameCounter = book->GetFrame();
	if (frameCounter >= 4) {
		RenderArray("MAIN");
		RenderArray("MISC");
		RenderArray("GUI");
		menuOptions[currentOption].selectorF->box.SetPos(Vec2(menuOptions[currentOption].button->box.x + menuOptions[currentOption].button->box.w, menuOptions[currentOption].button->box.y) + Vec2(0, 8));
		menuOptions[currentOption].selectorB->box.SetPos(Vec2(menuOptions[currentOption].button->box.x - menuOptions[currentOption].selectorB->box.w, menuOptions[currentOption].button->box.y) + Vec2(0, 8));
		menuOptions[currentOption].selectorF->Render();
		menuOptions[currentOption].selectorB->Render();
	}
}

void PauseState::SetOption(int i) {
	if (!menuOptions.size())
		return;

	currentOption = currentOption + i;
	if (currentOption<0) {
		currentOption = menuOptions.size() + i;
	}
	else {
		// It does nothing.
	}

	currentOption = currentOption % menuOptions.size();

	if (menuOptions[currentOption].selectable == false) {
		SetOption(i);
		return;
	}
	else {
		// It does nothing.
	}
}

bool PauseState::SelectedOptionIs(std::string opt) {
	return menuOptions[currentOption].key == opt;
}