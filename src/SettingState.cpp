#include "SettingState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "TitleState.h"
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

bool SortRenderOrder_TS2(std::shared_ptr<GameObject> i, std::shared_ptr<GameObject> j) { return (i->box.y + i->box.h < j->box.y + j->box.h); }

SettingState::SettingState() : State() {
	GameObject* goSelectorF;
	GameObject* goSelectorB;
	Sprite * novo;

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
	goBook = new GameObject();
	book = new Sprite(*goBook, "assets/img/Title/passando.png", 6, 0.4, false, 0.0);
	book->SetScale(Vec2(4,4)*GameData::globalScale);
	goBook->AddComponent(book);
	AddObject(goBook, "OPEN");

	//pageEffectEsq
	go = new GameObject();
	effect = new Sprite(*go, "assets/img/Title/pageEffectEsq.png", 4, 0.5, false, 0.0);
	effect->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(effect);
	go->AddComponent(new CameraFollower(*go, (Vec2(275, 300)*GameData::globalScale) - (go->box.GetSize() / 2)));
	AddObject(go, "APPEAR");

	//pageEffectDir
	go = new GameObject();
	effect = new Sprite(*go, "assets/img/Title/pageEffectDir.png", 4, 0.5, false, 0.0);
	effect->SetScale(Vec2(4, 4)*GameData::globalScale);
	go->AddComponent(effect);
	go->AddComponent(new CameraFollower(*go, (Vec2(750, 300)*GameData::globalScale) - (go->box.GetSize() / 2)));
	AddObject(go, "APPEAR");

	//TileMap
	go = new GameObject();
	set = new TileSet(*go, "assets/img/tileSet.png", 64, 64);
	TileMap* map = new TileMap(*go, set, "assets/map/tileMap.txt");
	go->AddComponent(map);
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	//Buttons

	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/ScreenButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, (Vec2(275, 180)*GameData::globalScale) - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "Screen",Vec2(275, 180) - (go->box.GetSize() / 2), goSelectorF,goSelectorB, go, true, 0 });

	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/ControllersButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, (Vec2(275, 280)*GameData::globalScale) - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "Controllers",Vec2(275, 280) - (go->box.GetSize() / 2),goSelectorF,goSelectorB, go, true, 0 });

	go = new GameObject();
	novo = new Sprite(*go, "assets/img/Title/BackButton.png", 1, 0.1, false, 0.0);
	novo->SetScale(Vec2(3, 3)*GameData::globalScale);
	go->AddComponent(novo);
	go->AddComponent(new CameraFollower(*go, (Vec2(275,380) * GameData::globalScale) - (go->box.GetSize() / 2)));
	AddObject(go, "GUI");

	menuOptions.push_back({ "Back",Vec2(275, 380) - (go->box.GetSize() / 2),goSelectorF,goSelectorB, go, true, 0 });

}

SettingState::~SettingState() {
	delete set;
}

void SettingState::LoadAssets() {

}

void SettingState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void SettingState::Pause() {
	for(int i = objects["MAIN"].size() - 1; i >= 0 ; i--) {
		if(objects["MAIN"][i]->GetComponent("NPC") && !objects["MAIN"][i]->GetComponent("Boss")) {
			if(Camera::GetFocus() == objects["MAIN"][i].get())
				Camera::Unfollow();
			objects["MAIN"].erase(objects["MAIN"].begin() + i);
		}
	}
}

void SettingState::Resume() {
	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	Camera::pos = Vec2(0, 0);
	book->SetFrame(0);
	book->SetTime(0);
	if(GameData::playerVictory) {
		set->SetTileSet("assets/img/tileSet.png");

	/*	//NPCs
		for (int i = 0; i < 10; i++) {
			GameObject*  go = new GameObject();
			go->AddComponentAsFirst(new NPC(*go, NPCList[rand()%NPCList.size()]));
			go->box.SetCenter(rand() % mw, rand() % mh);
			AddObject(go, "MAIN");
		}*/
	}
	else {
		set->SetTileSet("assets/img/bossTileSet.png");

		/*//Monsters
		for (int i = 0; i < 10; i++) {
			GameObject* go = new GameObject();
			Monster* mon = new Monster(*go, NPCList[rand()%NPCList.size()]);
			mon->Transform();
			go->AddComponentAsFirst(mon);
			go->box.SetCenter(rand() % mw, rand() % mh);

			AddObject(go, "MAIN");
		}*/
	}
	if(GameData::bossStageUnlocked) {
		Text* txt = (Text*)objects["GUI"][1]->GetComponent("Text");
		txt->SetColor(SDL_Color { 0,0,0,128 });
	}
}

void SettingState::CollisionCheck() {
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

void SettingState::DeletionCheck() {
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

void SettingState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	waitingConfirm = false;
		if (controllerSelected) {
			if (waitingKey) {
				InputManager::GetLastKey();
				if (GameData::key != 13) {
					Text * nText;
					for (unsigned i = 0; i < settingsText.size(); i++) {
						if (settingsText[i].lock()->GetComponent("Text") == settingOptions[currentOption].text->GetComponent("Text")) {
							nText = (Text*)settingsText[i].lock()->GetComponent("Text");
							nText->SetText(SDL_GetKeyName(GameData::key));
						}
					}
					waitingConfirm = true;
				}
				if (waitingConfirm) {
					waitingKey = false;
					if (currentOption == 0) {
						nUp = GameData::key;
					}
					if (currentOption == 1) {
						nDown = GameData::key;
					}
					if (currentOption == 2) {
						nLeft = GameData::key;
					}
					if (currentOption == 3) {
						nRight = GameData::key;
					}
					if (currentOption == 4) {
						nBubbles = GameData::key;
					}
					if (currentOption == 5) {
						nFireball = GameData::key;
					}
					if (currentOption == 6) {
						nCapture = GameData::key;
					}
				}
			}
			else {
				if (InputManager::KeyPress(GameData::UP_MOV)) {
					SetOption(settingOptions, -1);
				}
				if (InputManager::KeyPress(GameData::DOWN_MOV)) {
					SetOption(settingOptions, 1);
				}
				if (InputManager::KeyPress(SDLK_KP_ENTER) || InputManager::KeyPress(CONFIRM)) {
					// Check if the event was "NewGame".
					if (SelectedOptionIs(settingOptions, "Up")) {
						Text * nText;
						int key = 0;
						for (unsigned i = 0; i < settingsText.size(); i++) {
							if (settingsText[i].lock()->GetComponent("Text") == settingOptions[currentOption].text->GetComponent("Text")) {
								nText = (Text*)settingsText[i].lock()->GetComponent("Text");
								nText->SetText("Enter New");
							}
						}
						waitingKey = true;
					}
					if (SelectedOptionIs(settingOptions, "Down")) {
						Text * nText;
						int key = 0;
						for (unsigned i = 0; i < settingsText.size(); i++) {
							if (settingsText[i].lock()->GetComponent("Text") == settingOptions[currentOption].text->GetComponent("Text")) {
								nText = (Text*)settingsText[i].lock()->GetComponent("Text");
								nText->SetText("Enter New");
							}
						}
						waitingKey = true;
					}
					if (SelectedOptionIs(settingOptions, "Left")) {
						Text * nText;
						int key = 0;
						for (unsigned i = 0; i < settingsText.size(); i++) {
							if (settingsText[i].lock()->GetComponent("Text") == settingOptions[currentOption].text->GetComponent("Text")) {
								nText = (Text*)settingsText[i].lock()->GetComponent("Text");
								nText->SetText("Enter New");
							}
						}
						waitingKey = true;
					}
					if (SelectedOptionIs(settingOptions, "Right")) {
						Text * nText;
						int key = 0;
						for (unsigned i = 0; i < settingsText.size(); i++) {
							if (settingsText[i].lock()->GetComponent("Text") == settingOptions[currentOption].text->GetComponent("Text")) {
								nText = (Text*)settingsText[i].lock()->GetComponent("Text");
								nText->SetText("Enter New");
							}
						}
						waitingKey = true;
					}
					if (SelectedOptionIs(settingOptions, "Attack1")) {
						Text * nText;
						int key = 0;
						for (unsigned i = 0; i < settingsText.size(); i++) {
							if (settingsText[i].lock()->GetComponent("Text") == settingOptions[currentOption].text->GetComponent("Text")) {
								nText = (Text*)settingsText[i].lock()->GetComponent("Text");
								nText->SetText("Enter New");
							}
						}
						waitingKey = true;
					}
					if (SelectedOptionIs(settingOptions, "Attack2")) {
						Text * nText;
						int key = 0;
						for (unsigned i = 0; i < settingsText.size(); i++) {
							if (settingsText[i].lock()->GetComponent("Text") == settingOptions[currentOption].text->GetComponent("Text")) {
								nText = (Text*)settingsText[i].lock()->GetComponent("Text");
								nText->SetText("Enter New");
							}
						}
						waitingKey = true;
					}
					if (SelectedOptionIs(settingOptions, "Attack3")) {
						Text * nText;
						int key = 0;
						for (unsigned i = 0; i < settingsText.size(); i++) {
							if (settingsText[i].lock()->GetComponent("Text") == settingOptions[currentOption].text->GetComponent("Text")) {
								nText = (Text*)settingsText[i].lock()->GetComponent("Text");
								nText->SetText("Enter New");
							}
						}
						waitingKey = true;
					}
					if (SelectedOptionIs(settingOptions, "CONFIRMAR")) {
						
						GameData::UP_MOV = nUp;
						GameData::DOWN_MOV = nDown;
						GameData::LEFT_MOV = nLeft;
						GameData::RIGHT_MOV = nRight;
						GameData::MAGIC_BUBBLES = nBubbles;
						GameData::MAGIC_FIREBALL = nFireball;
						GameData::MAGIC_CAPTURE = nCapture;
						waitingKey = false;
					}
					if (SelectedOptionIs(settingOptions, "Back")) {
						currentOption = 0;
						controllerSelected = false;
						waitingKey = false;
					}
				}
			}
		}
		else {
			if (InputManager::KeyPress(GameData::UP_MOV)) {
				SetOption(menuOptions, -1);
			}
			if (InputManager::KeyPress(GameData::DOWN_MOV)) {
				SetOption(menuOptions, 1);
			}
			if (InputManager::KeyPress(SDLK_KP_ENTER) || InputManager::KeyPress(CONFIRM)) {

				// Check if the event was "NewGame".
				if (SelectedOptionIs(menuOptions, "Screen")) {
					int w, h;
					SDL_SetWindowFullscreen(GameData::window, SDL_WINDOW_FULLSCREEN);
					SDL_GetWindowSize(GameData::window, &w, &h);
					GameData::globalScale = Vec2(w/GameData::mapSize.x, h / GameData::mapSize.y);
					GameData::fullscreen = true;
					popRequested = true;
					//Game::GetInstance().Push(new SettingState());
				}
				// Check if the event was "Settings".
				else if (SelectedOptionIs(menuOptions, "Controllers")) {
					currentOption = 0;
					controllerSelected = true;
					GameObject* goSelectorF;
					GameObject* goSelectorB;
					Sprite * novo;

					//MenuSelector
					goSelectorF = new GameObject();
					Sprite* selector = new Sprite(*goSelectorF, "assets/img/Title/SelectorF.png", 1, 0.01, false, 0.0);
					selector->SetScale(Vec2(3, 3)*GameData::globalScale);
					goSelectorF->AddComponent(selector);

					goSelectorB = new GameObject();
					selector = new Sprite(*goSelectorB, "assets/img/Title/SelectorB.png", 1, 0.01, false, 0.0);
					selector->SetScale(Vec2(3, 3)*GameData::globalScale);
					goSelectorB->AddComponent(selector);

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 40, "Change Controllers", SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(750, 150)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, "Change UP:", SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(700, 200)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, SDL_GetKeyName(GameData::UP_MOV), SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(800, 200)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					settingsText.emplace_back(Game::GetInstance().GetCurrentState().AddObject(settingsMenu, "POSGUI"));

					settingOptions.push_back({ "Up",Vec2(800, 200) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, "Change Down:", SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(700, 225)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, SDL_GetKeyName(GameData::DOWN_MOV), SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(800, 225)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					settingsText.emplace_back(Game::GetInstance().GetCurrentState().AddObject(settingsMenu, "POSGUI"));

					settingOptions.push_back({ "Down",Vec2(800, 225) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, "Change Left:", SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(700, 250)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, SDL_GetKeyName(GameData::LEFT_MOV), SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(800, 250)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					settingsText.emplace_back(Game::GetInstance().GetCurrentState().AddObject(settingsMenu, "POSGUI"));

					settingOptions.push_back({ "Left",Vec2(800, 250) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, "Change Right:", SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(700, 275)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, SDL_GetKeyName(GameData::RIGHT_MOV), SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(800, 275)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					settingsText.emplace_back(Game::GetInstance().GetCurrentState().AddObject(settingsMenu, "POSGUI"));

					settingOptions.push_back({ "Right",Vec2(800, 275) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, "Change Attack 1:", SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(700, 300)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, SDL_GetKeyName(GameData::MAGIC_BUBBLES), SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(800, 300)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					settingsText.emplace_back(Game::GetInstance().GetCurrentState().AddObject(settingsMenu, "POSGUI"));

					settingOptions.push_back({ "Attack1",Vec2(800, 300) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, "Change Attack 2:", SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(700, 325)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, SDL_GetKeyName(GameData::MAGIC_FIREBALL), SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(800, 325)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					settingsText.emplace_back(Game::GetInstance().GetCurrentState().AddObject(settingsMenu, "POSGUI"));

					settingOptions.push_back({ "Attack2",Vec2(800, 325) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, "Change Attack 3:", SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(700, 350)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingsMenu = new GameObject();
					settingsMenu->AddComponent(new Text(*settingsMenu, "assets/font/VT323.ttf", 25, SDL_GetKeyName(GameData::MAGIC_CAPTURE), SDL_Color{ 0,0,0,128 }, Text::SOLID));
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(800, 350)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					settingsText.emplace_back(Game::GetInstance().GetCurrentState().AddObject(settingsMenu, "POSGUI"));

					settingOptions.push_back({ "Attack3",Vec2(800, 350) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });

					settingsMenu = new GameObject();
					novo = new Sprite(*settingsMenu, "assets/img/Title/ConfirmButton.png", 1, 0.1, false, 0.0);
					novo->SetScale(Vec2(2, 2)*GameData::globalScale);
					settingsMenu->AddComponent(novo);
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(750, 400)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingOptions.push_back({ "CONFIRMAR",Vec2(750, 400) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });

					settingsMenu = new GameObject();
					novo = new Sprite(*settingsMenu, "assets/img/Title/BackButton.png", 1, 0.1, false, 0.0);
					novo->SetScale(Vec2(2, 2)*GameData::globalScale);
					settingsMenu->AddComponent(novo);
					settingsMenu->AddComponent(new CameraFollower(*settingsMenu, (Vec2(750, 450)*GameData::globalScale) - (settingsMenu->box.GetSize() / 2)));
					AddObject(settingsMenu, "POSGUI");

					settingOptions.push_back({ "Back",Vec2(750, 450) - (settingsMenu->box.GetSize() / 2), goSelectorF,goSelectorB, settingsMenu, true, 0 });
				}
				// Check if the event was "Exit".
				else if (SelectedOptionIs(menuOptions, "Back")) {
					popRequested = true;
				}
			}
		}
	/*}else if (InputManager::KeyPress(SDLK_KP_ENTER) || InputManager::KeyPress(CONFIRM)) {
		//Page
		go = new GameObject();
		page = new Sprite(*go, "assets/img/Title/passando.png", 6, 0.4, false, 0.0);
		page->SetScale(Vec2(4, 4));
		go->AddComponent(page);
		AddObject(go, "POS");
		waitingEnter = true;
	}*/

	if(InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	UpdateArray(dt, "BG");
	UpdateArray(dt, "OPEN");
	frameCounter = book->GetFrame();
	if (frameCounter >= 5) {
		UpdateArray(dt, "APPEAR");
		frameCounter = effect->GetFrame();
		if (frameCounter >= 3) {
			UpdateArray(dt, "GUI");
			if (controllerSelected) {
					UpdateArray(dt, "MAIN");
					UpdateArray(dt, "MISC");
					UpdateArray(dt, "POSGUI");
					CollisionCheck();
					DeletionCheck();

					std::sort(objects["EFFECT"].begin(), objects["EFFECT"].end(), SortRenderOrder_TS2);
					std::sort(objects["MAIN"].begin(), objects["MAIN"].end(), SortRenderOrder_TS2);
			}
		}
	}
}

void SettingState::Render() {
	RenderArray("BG");
	RenderArray("OPEN");
	frameCounter = book->GetFrame();
	if (frameCounter >= 5) {
		RenderArray("APPEAR");
		frameCounter = effect->GetFrame();
		if (frameCounter >= 3) {
			RenderArray("GUI");
			if (!controllerSelected) {
				menuOptions[currentOption].selectorF->box.SetPos(Vec2(menuOptions[currentOption].text->box.x + menuOptions[currentOption].text->box.w, menuOptions[currentOption].text->box.y) + Vec2(0, 8));
				menuOptions[currentOption].selectorB->box.SetPos(Vec2(menuOptions[currentOption].text->box.x - menuOptions[currentOption].selectorB->box.w, menuOptions[currentOption].text->box.y) + Vec2(0, 8));
				menuOptions[currentOption].selectorF->Render();
				menuOptions[currentOption].selectorB->Render();
			}
			if (controllerSelected) {
				RenderArray("MAIN");
				RenderArray("MISC");
				RenderArray("POSGUI");
				settingOptions[currentOption].selectorF->box.SetPos(Vec2(settingOptions[currentOption].text->box.x + settingOptions[currentOption].text->box.w, settingOptions[currentOption].text->box.y) + Vec2(10, 0));
				settingOptions[currentOption].selectorF->Render();
			}
		}
	}
}

void SettingState::SetOption(std::vector<Option> menuOptions,int i) {
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

bool SettingState::SelectedOptionIs(std::vector<Option> menuOptions,std::string opt) {
	return menuOptions[currentOption].key == opt;
}