#include "TitleState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "SettingState.h"
#include "StageState.h"
#include "BossStageState.h"
#include "TutorialStageState.h"

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
	GameObject* goSelectorF;
	GameObject* goSelectorB;
	Sprite * novo;

	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	Camera::pos = Vec2(0, 0);

	//MenuSelector

	/*goSelector = new GameObject();
	goSelector->AddComponent(new Sprite(*goBook, "assets/img/bookM.png"));*/

	goSelectorF = new GameObject();
	Sprite* selector = new Sprite(*goSelectorF, "assets/img/Title/SelectorF.png", 1, 0.01, false);
	selector->SetScale(Vec2(3, 3)*GameData::globalScale);
	goSelectorF->AddComponent(selector);

	goSelectorB = new GameObject();
	selector = new Sprite(*goSelectorB, "assets/img/Title/SelectorB.png", 1, 0.01, false);
	selector->SetScale(Vec2(3, 3)*GameData::globalScale);
	goSelectorB->AddComponent(selector);

	//MenuBook
	go = new GameObject();
	book = new Sprite(*go, "assets/img/Title/ABRINDO.png", 5, 0.1, false);
	book->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(book);
	go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
	AddObject(go, "OPEN");

	//pageEffectEsq
	go = new GameObject();
	effect = new Sprite(*go, "assets/img/Title/pageEffectEsq.png", 4, 0.15, false);
	effect->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(effect);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 300)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "APPEAR");

	//pageEffectDir
	go = new GameObject();
	effect = new Sprite(*go, "assets/img/Title/pageEffectDir.png", 4, 0.15, false);
	effect->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(effect);
	go->AddComponent(new CameraFollower(*go, Vec2(750, 300)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "APPEAR");

	//MyName
	go = new GameObject();
	titleEsq = new Sprite(*go, "assets/img/Title/myname.png", 15, 0.05, false);
	titleEsq->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(titleEsq);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 275)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "TITLE1");

	//Title
	go = new GameObject();
	titleDir = new Sprite(*go, "assets/img/Title/lucity.png", 7, 0.05, false);
	titleDir->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(titleDir);
	go->AddComponent(new CameraFollower(*go, Vec2(750, 275)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "TITLE2");

	//Title
	go = new GameObject();
	press = new Sprite(*go, "assets/img/Title/pressButton.png", 2, 0.2, true);
	press->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(press);
	go->AddComponent(new CameraFollower(*go, Vec2(750, 475)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "PRESS");

	//pageEffectEsq
	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/pageEffectEsq.png", 4, 0.15, false);
	novo->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 300)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	//pageEffectDir
	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/pageEffectDir.png", 4, 0.15, false);
	novo->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, Vec2(750, 300)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	//NewGame
	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/NewGameButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 180)*GameData::globalScale - (go->box.GetSize()/2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "NewGame",Vec2(275, 180) - (go->box.GetSize() / 2), goSelectorF,goSelectorB, go, true, 0 });

	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/SettingsButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 280)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "Settings",Vec2(275, 220) - (go->box.GetSize() / 2),goSelectorF,goSelectorB, go, true, 0 });

	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/ExitButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, Vec2(275, 380)*GameData::globalScale - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "Exit",Vec2(275, 260) - (go->box.GetSize() / 2),goSelectorF,goSelectorB, go, true, 0 });

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

}

void TitleState::Resume() {
	/*int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	Camera::pos = Vec2(0, 0);
	if (GameData::fullscreen) {
		popRequested = true;
		Game::GetInstance().Push(new TitleState());
	}
	else {
		Sprite * sprite;
		Vec2 oScale;
		book->Deactivate();
		press->Deactivate();
		page->SetFrame(0);
		//effectFE->SetFrame(0);
		//effectFD->SetFrame(0);
		//resume = true;
		//waitingEnter = true;

		if (GameData::playerVictory) {
			set->SetTileSet("assets/img/tileSet.png");
		}
		if (GameData::bossStageUnlocked) {
			Text* txt = (Text*)objects["GUI"][1]->GetComponent("Text");
			txt->SetColor(SDL_Color{ 0,0,0,128 });
		}
	}*/
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
	if (waitingEnter) {

		if (InputManager::KeyPress(GameData::UP_MOV)) {
			SetOption(menuOptions, -1);
		}
		if (InputManager::KeyPress(GameData::DOWN_MOV)) {
			SetOption(menuOptions, 1);
		}
		if (InputManager::KeyPress(SDLK_KP_ENTER) || InputManager::KeyPress(CONFIRM)) {

			// Check if the event was "NewGame".
			if (SelectedOptionIs(menuOptions, "NewGame")) {
				Game::GetInstance().Push(new StageState());
			}
			// Check if the event was "Settings".
			else if (SelectedOptionIs(menuOptions, "Settings")) {
				Game::GetInstance().Push(new SettingState());
			}
			// Check if the event was "Exit".
			else if (SelectedOptionIs(menuOptions, "Exit")) {
				quitRequested = true; // Set to truth the variable that is responsible to validate the quit request of the game.
			}
		} else if (InputManager::KeyPress(SDLK_BACKSPACE)) {
				Game::GetInstance().Push(new TutorialStageState());
		}
	}
	else if ((InputManager::KeyPress(SDLK_KP_ENTER) || InputManager::KeyPress(CONFIRM))) {
		//PageFaddingEsq
		go = new GameObject();
		effectF = new Sprite(*go, "assets/img/Title/pageFaddingEsq.png", 4, 0.2, false, 0.0);
		effectF->SetScale(Vec2(4, 4)*GameData::globalScale);
		go->AddComponent(effectF);
		go->AddComponent(new CameraFollower(*go, Vec2(275, 300)*GameData::globalScale - (go->box.GetSize() / 2)));
		AddObject(go, "POS1");

		//PageFaddingDir
		go = new GameObject();
		effectF = new Sprite(*go, "assets/img/Title/pageFaddingDir.png", 4, 0.2, false, 0.0);
		effectF->SetScale(Vec2(4, 4)*GameData::globalScale);
		go->AddComponent(effectF);
		go->AddComponent(new CameraFollower(*go, Vec2(750, 300)*GameData::globalScale - (go->box.GetSize() / 2)));
		AddObject(go, "POS1");

		//Page
		go = new GameObject();
		page = new Sprite(*go, "assets/img/Title/passando.png", 6, 0.05, false, 0.0);
		page->SetScale(Vec2(4, 4)*GameData::globalScale);
		go->AddComponent(page);
		go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
		AddObject(go, "POS2");

		waitingEnter = true;
	}
	if (GameData::fullscreen && page==nullptr) {
		//Page
		go = new GameObject();
		page = new Sprite(*go, "assets/img/Title/passando.png", 6, 0.05, false, 0.0);
		page->SetScale(Vec2(4, 4)*GameData::globalScale);
		go->AddComponent(page);
		go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
		AddObject(go, "POS2");

		waitingEnter = true;
	}
	if (InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	if (!GameData::fullscreen) {
		UpdateArray(dt, "BG");
		UpdateArray(dt, "OPEN");
		frameCounter = book->GetFrame();
		if (frameCounter >= 4) {
			UpdateArray(dt, "APPEAR");
			frameCounter = effect->GetFrame();
			if (frameCounter >= 3) {
				UpdateArray(dt, "TITLE1");
				frameCounter = titleEsq->GetFrame();
				if (frameCounter >= 14) {
					UpdateArray(dt, "TITLE2");
					frameCounter = titleDir->GetFrame();
					if (frameCounter >= 6) {
						UpdateArray(dt, "PRESS");
						if (waitingEnter) {
							UpdateArray(dt, "POS1");
							frameCounterPage = effectF->GetFrame();
							if (frameCounterPage >= 3) {
								UpdateArray(dt, "POS2");
								frameCounterPage = page->GetFrame();
								if (frameCounterPage >= 5) {
									SDL_Delay(30);
									UpdateArray(dt, "MAIN");
									UpdateArray(dt, "MISC");
									UpdateArray(dt, "GUI");
									CollisionCheck();
									DeletionCheck();

									std::sort(objects["EFFECT"].begin(), objects["EFFECT"].end(), SortRenderOrder_TS);
									std::sort(objects["MAIN"].begin(), objects["MAIN"].end(), SortRenderOrder_TS);
								}
							}
						}
					}
				}
			}
		}
	}
	else {
		UpdateArray(dt, "BG");
		UpdateArray(dt, "POS2");
		frameCounterPage = page->GetFrame();
		if (frameCounterPage >= 5) {
			SDL_Delay(30);
			UpdateArray(dt, "MAIN");
			UpdateArray(dt, "MISC");
			UpdateArray(dt, "GUI");
			CollisionCheck();
			DeletionCheck();

			std::sort(objects["EFFECT"].begin(), objects["EFFECT"].end(), SortRenderOrder_TS);
			std::sort(objects["MAIN"].begin(), objects["MAIN"].end(), SortRenderOrder_TS);
		}
	}
}

void TitleState::Render() {

	if (!GameData::fullscreen) {
		RenderArray("BG");
		RenderArray("OPEN");
		frameCounter = book->GetFrame();
		if (frameCounter >= 4) {
			RenderArray("APPEAR");
			frameCounter = effect->GetFrame();
			if (frameCounter >= 3) {
				RenderArray("TITLE1");
				frameCounter = titleEsq->GetFrame();
				if (frameCounter >= 14) {
					RenderArray("TITLE2");
					frameCounter = titleDir->GetFrame();
					if (frameCounter >= 6) {
						RenderArray("PRESS");
						if (waitingEnter) {
							RenderArray("POS1");
							frameCounterPage = effectF->GetFrame();
							if (frameCounterPage >= 3) {
								RenderArray("POS2");
								frameCounterPage = page->GetFrame();
								if (frameCounterPage >= 5) {
									RenderArray("MAIN");
									RenderArray("MISC");
									RenderArray("GUI");
									menuOptions[currentOption].selectorF->box.SetPos(Vec2(menuOptions[currentOption].button->box.x + menuOptions[currentOption].button->box.w, menuOptions[currentOption].button->box.y) + Vec2(0, 8));
									menuOptions[currentOption].selectorB->box.SetPos(Vec2(menuOptions[currentOption].button->box.x - menuOptions[currentOption].selectorB->box.w, menuOptions[currentOption].button->box.y) + Vec2(0, 8));
									menuOptions[currentOption].selectorF->Render();
									menuOptions[currentOption].selectorB->Render();
								}
							}
						}
					}
				}
			}
		}
	}
	else {
		RenderArray("BG");
		RenderArray("POS2");
		frameCounterPage = page->GetFrame();
		if (frameCounterPage >= 5) {
			RenderArray("MAIN");
			RenderArray("MISC");
			RenderArray("GUI");
			menuOptions[currentOption].selectorF->box.SetPos(Vec2(menuOptions[currentOption].button->box.x + menuOptions[currentOption].button->box.w, menuOptions[currentOption].button->box.y) + Vec2(0, 8));
			menuOptions[currentOption].selectorB->box.SetPos(Vec2(menuOptions[currentOption].button->box.x - menuOptions[currentOption].selectorB->box.w, menuOptions[currentOption].button->box.y) + Vec2(0, 8));
			menuOptions[currentOption].selectorF->Render();
			menuOptions[currentOption].selectorB->Render();
		}

	}
}

void TitleState::SetOption(std::vector<Option> menuOptions,int i) {
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
		SetOption(menuOptions,i);
		return;
	}
	else {
		// It does nothing.
	}
}

bool TitleState::SelectedOptionIs(std::vector<Option> menuOptions,std::string opt) {
	return menuOptions[currentOption].key == opt;
}
