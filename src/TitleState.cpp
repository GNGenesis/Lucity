#include "TitleState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"

#include "TutorialStageState.h"
#include "StageState.h"
#include "BossStageState.h"

#include "Sprite.h"
#include "Text.h"
#include "Button.h"
#include "CameraFollower.h"

#include <algorithm>

TitleState::TitleState() : State() {
	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	Camera::pos = Vec2(0, 0);

	GameData::popAgain = false;

	GameObject* go;
	Sprite* sp;

	animationCount = 0;
	layer = "main";
	index = 0;
	waitingKey = false;
	waitingConfirmation = false;
	reopen = false;

	//Opening Animations
	if(true) {
		//Opening Book
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/title/opening.png", 5, 0.1, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
		AddObject(go, "BOOK");
		go->box.SetPos(Vec2(0, 0));

		//Pass Page Book
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/title/passing.png", 6, 0.1, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
		AddObject(go, "PASS");
		go->box.SetPos(Vec2(0, 0));
		go->Deactivate();

		//Page Left
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/title/effect_left.png", 5, 0.15, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(275, 300) - (go->box.GetSize() / 2)));
		AddObject(go, "PAGES");
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Page Right
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/title/effect_right.png", 5, 0.15, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(750, 300) - (go->box.GetSize() / 2)));
		AddObject(go, "PAGES");
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//MyName
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/title/myname.png", 15, 0.05, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(275, 275) - (go->box.GetSize() / 2)));
		AddObject(go, "TITLE1");
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Title
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/title/lucity.png", 7, 0.05, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(750, 275) - (go->box.GetSize() / 2)));
		AddObject(go, "TITLE2");
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Press Flag
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/title/press.png", 2, 0.4, true);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(750, 475) - (go->box.GetSize() / 2)));
		AddObject(go, "PRESS");
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();
	}

	go = new GameObject();
	sp = new Sprite(*go, "assets/img/title/selector_left.png");
	sp->SetScale(Vec2(3, 3));
	go->AddComponent(sp);
	buttons["selected"].emplace_back(AddObject(go, "HUD"));
	go->box.SetPos(Vec2(-2000, -2000));
	go->Deactivate();

	go = new GameObject();
	sp = new Sprite(*go, "assets/img/title/selector_right.png");
	sp->SetScale(Vec2(3, 3));
	go->AddComponent(sp);
	buttons["selected"].emplace_back(AddObject(go, "HUD"));
	go->box.SetPos(Vec2(-2000, -2000));
	go->Deactivate();

	//Main Menu: Stage Select
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Stage Select", Vec2(275, 180)));
	buttons["main"].emplace_back(AddObject(go, "MAIN"));
	go->box.SetPos(Vec2(-2000, -2000));
	go->Deactivate();

	//Stage Menu
	if(true) {
		//Stage Menu: Tutorial
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Tutorial", Vec2(749, 180)));
		buttons["stage"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();
		
		//Stage Menu: City
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "City", Vec2(749, 220)));
		buttons["stage"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();
		
		//Stage Menu: Boss
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Boss", Vec2(749, 260)));
		buttons["stage"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();
	}
	
	//Main Menu: Settings
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Settings", Vec2(275, 220)));
	buttons["main"].emplace_back(AddObject(go, "MAIN"));
	go->box.SetPos(Vec2(-2000, -2000));
	go->Deactivate();
	
	//Main Menu: Quit
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Quit", Vec2(275, 380)));
	buttons["main"].emplace_back(AddObject(go, "MAIN"));
	go->box.SetPos(Vec2(-2000, -2000));
	go->Deactivate();
	
	//Settings Menu: Controls
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Controls", Vec2(275, 180)));
	buttons["settings"].emplace_back(AddObject(go, "MAIN"));
	go->box.SetPos(Vec2(-2000, -2000));
	go->Deactivate();

	//Controls Menu
	if(true) {
		//Controls Menu: UP
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Up Movement Key", Vec2(695, 150)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: UP Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Up", Vec2(870, 150)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();
		
		//Controls Menu: DOWN
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Down Movement Key", Vec2(695, 190)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: DOWN Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Down", Vec2(870, 190)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();
		
		//Controls Menu: LEFT
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Left Movement Key", Vec2(695, 230)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: LEFT Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Left", Vec2(870, 230)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: RIGHT
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Right Movement Key", Vec2(695, 270)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: RIGHT Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Right", Vec2(870, 270)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: ACTION 1
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Attack 1 Key", Vec2(695, 310)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: ACTION 1 Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "1", Vec2(870, 310)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: ACTION 2
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Attack 2 Key", Vec2(695, 350)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: ACTION 2 Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "2", Vec2(870, 350)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: ACTION 3
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Attack 3 Key", Vec2(695, 390)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: ACTION 3 Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "3", Vec2(870, 390)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: PAUSE
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Pause Menu Key", Vec2(695, 430)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Controls Menu: ACTION 4 Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Escape", Vec2(870, 430)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();
	}

	//Settings Menu: Screen
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Screen", Vec2(275, 220)));
	buttons["settings"].emplace_back(AddObject(go, "MAIN"));
	go->box.SetPos(Vec2(-2000, -2000));
	go->Deactivate();

	//Screen Menu
	if(true) {
		//Screen Menu: fullscreen
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Fullsceen", Vec2(749, 180)));
		buttons["screen"].emplace_back(AddObject(go, "MAIN"));
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();
	}
	
	//Settings Menu: Back
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Back", Vec2(275, 380)));
	buttons["settings"].emplace_back(AddObject(go, "MAIN"));
	go->box.SetPos(Vec2(-2000, -2000));
	go->Deactivate();
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
	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	Camera::pos = Vec2(0, 0);

	GameData::popAgain = false;

	animationCount = 0;
	reopen = true;
	for(unsigned int i = 0; i < objects["BOOK"].size(); i++) {
		Sprite* sp = (Sprite*) objects["BOOK"][i]->GetComponent("Sprite");
		if(sp) {
			sp->GoBack();
		}
	}
	for(unsigned int i = 0; i < objects["PASS"].size(); i++) {
		Sprite* sp = (Sprite*) objects["PASS"][i]->GetComponent("Sprite");
		if(sp) {
			sp->SetFrame(0);
		}
	}
	for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
		Sprite* sp = (Sprite*) objects["PAGES"][i]->GetComponent("Sprite");
		if(sp) {
			sp->GoBack();
		}
	}
	for(unsigned int i = 0; i < objects["TITLE1"].size(); i++) {
		Sprite* sp = (Sprite*) objects["TITLE1"][i]->GetComponent("Sprite");
		if(sp) {
			sp->SetFrame(0);
		}
	}
	for(unsigned int i = 0; i < objects["TITLE2"].size(); i++) {
		Sprite* sp = (Sprite*) objects["TITLE2"][i]->GetComponent("Sprite");
		if(sp) {
			sp->SetFrame(0);
		}
	}
}

void TitleState::Opening() {
	if(animationCount == 0) {
		if(animationT.Get() > 0.5) {
			animationCount++;
			for(unsigned int i = 0; i < objects["BOOK"].size(); i++) {
				objects["BOOK"][i]->Deactivate();
			}
			for(unsigned int i = 0; i < objects["PASS"].size(); i++) {
				objects["PASS"][i]->Activate();
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 1) {
		if(animationT.Get() > 0.6) {
			if(reopen)
				animationCount = 8;
			else
				animationCount++;
			for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
				objects["PAGES"][i]->Activate();
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 2) {
		if(animationT.Get() > 0.75) {
			animationCount++;
			for(unsigned int i = 0; i < objects["TITLE1"].size(); i++) {
				objects["TITLE1"][i]->Activate();
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 3) {
		if(animationT.Get() > 0.75) {
			animationCount++;
			for(unsigned int i = 0; i < objects["TITLE2"].size(); i++) {
				objects["TITLE2"][i]->Activate();
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 4) {
		if(animationT.Get() > 0.35) {
			InputManager::ResetLastKey();
			animationCount++;
			for(unsigned int i = 0; i < objects["PRESS"].size(); i++) {
				objects["PRESS"][i]->Activate();
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 5) {
		InputManager::GetLastKey();
		if(GameData::key != NULL) {
			animationCount++;
			for(unsigned int i = 0; i < objects["TITLE1"].size(); i++) {
				objects["TITLE1"][i]->Deactivate();
			}
			for(unsigned int i = 0; i < objects["TITLE2"].size(); i++) {
				objects["TITLE2"][i]->Deactivate();
			}
			for(unsigned int i = 0; i < objects["PRESS"].size(); i++) {
				objects["PRESS"][i]->Deactivate();
			}
			for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
				Sprite* sp = (Sprite*) objects["PAGES"][i]->GetComponent("Sprite");
				if(sp) {
					sp->GoBack();
				}
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 6) {
		if(animationT.Get() > 0.75) {
			animationCount++;
			for(unsigned int i = 0; i < objects["PASS"].size(); i++) {
				Sprite* sp = (Sprite*) objects["PASS"][i]->GetComponent("Sprite");
				if(sp) {
					sp->SetFrame(0);
				}
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 7) {
		if(animationT.Get() > 0.6) {
			animationCount++;
			for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
				Sprite* sp = (Sprite*) objects["PAGES"][i]->GetComponent("Sprite");
				if(sp) {
					sp->GoBack();
				}
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 8) {
		if(animationT.Get() > 0.75) {
			animationCount = 16;
			for(unsigned int i = 0; i < buttons["selected"].size(); i++) {
				if(!buttons["selected"][i].expired()) {
					buttons["selected"][i].lock()->Activate();
				}
			}
			for(unsigned int i = 0; i < buttons["main"].size(); i++) {
				if(!buttons["main"][i].expired()) {
					buttons["main"][i].lock()->Activate();
				}
			}
			animationT.Restart();
		}
	}
}

void TitleState::Passing() {
	if(animationCount == 9) {
		animationCount++;
		for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
			Sprite* sp = (Sprite*) objects["PAGES"][i]->GetComponent("Sprite");
			if(sp) {
				sp->GoBack();
			}
		}
		animationT.Restart();
	}
	else if(animationCount == 10) {
		if(animationT.Get() > 0.75) {
			animationCount++;
			for(unsigned int i = 0; i < objects["PASS"].size(); i++) {
				Sprite* sp = (Sprite*) objects["PASS"][i]->GetComponent("Sprite");
				if(sp) {
					sp->SetFrame(0);
				}
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 11) {
		if(animationT.Get() > 0.6) {
			animationCount++;
			for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
				Sprite* sp = (Sprite*) objects["PAGES"][i]->GetComponent("Sprite");
				if(sp) {
					sp->GoBack();
				}
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 12) {
		if(animationT.Get() > 0.75) {
			animationCount = 16;
			for(unsigned int i = 0; i < buttons["selected"].size(); i++)
				if(!buttons["selected"][i].expired())
					buttons["selected"][i].lock()->Activate();

			for(unsigned int i = 0; i < buttons[layer].size(); i++)
				if(!buttons[layer][i].expired())
					buttons[layer][i].lock()->Activate();

			animationT.Restart();
		}
	}
}

void TitleState::Closing() {
	if(animationCount == 13) {
		animationCount++;
		for(unsigned int i = 0; i < buttons["selected"].size(); i++) {
			if(!buttons["selected"][i].expired()) {
				buttons["selected"][i].lock()->Deactivate();
			}
		}
		for(unsigned int i = 0; i < buttons["main"].size(); i++) {
			if(!buttons["main"][i].expired()) {
				buttons["main"][i].lock()->Deactivate();
			}
		}
		for(unsigned int i = 0; i < buttons["stage"].size(); i++) {
			if(!buttons["stage"][i].expired()) {
				buttons["stage"][i].lock()->Deactivate();
			}
		}
		for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
			Sprite* sp = (Sprite*) objects["PAGES"][i]->GetComponent("Sprite");
			if(sp) {
				sp->GoBack();
			}
		}
		animationT.Restart();
	}
	else if(animationCount == 14) {
		if(animationT.Get() > 0.6) {
			animationCount++;
			for(unsigned int i = 0; i < objects["PASS"].size(); i++) {
				objects["PASS"][i]->Deactivate();
			}
			for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
				objects["PAGES"][i]->Deactivate();
			}
			for(unsigned int i = 0; i < objects["BOOK"].size(); i++) {
				objects["BOOK"][i]->Activate();
				Sprite* sp = (Sprite*) objects["BOOK"][i]->GetComponent("Sprite");
				if(sp) {
					sp->GoBack();
				}
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 15) {
		if(animationT.Get() > 0.5) {
			animationT.Restart();
			if(layer == "stage") {
				if(index == 0) {
					Game::GetInstance().Push(new TutorialStageState());
				}
				else if(index == 1) {
					Game::GetInstance().Push(new StageState());
				}
				else if(index == 2) {
					Game::GetInstance().Push(new BossStageState());
				}
			}
			else if(layer == "main") {
				if(index == 2) {
					quitRequested = true;
				}
			}
		}
	}
}

void TitleState::SetKey() {
	if(!waitingConfirmation) {
		InputManager::GetLastKey();
		if(GameData::key != CONFIRM && GameData::key != NULL) {
			if(!buttons["keys"][index].expired()) {
				Button* b = (Button*) buttons["keys"][index].lock()->GetComponent("Button");
				if(b) {
					if(!b->GetText().expired()) {
						Vec2 size = b->GetText().lock()->box.GetSize();

						enteredKey = GameData::key;
						b->SetText(SDL_GetKeyName(GameData::key));
					
						CameraFollower* cf = (CameraFollower*) b->GetText().lock()->GetComponent("CameraFollower");
						if(cf) {
							cf->SetTruePos(cf->GetTruePos() + size/2 - b->GetText().lock()->box.GetSize()/2);
						}
					}
				}
			}
			waitingConfirmation = true;
		}
	}
	else {
		InputManager::GetLastKey();
		if(InputManager::KeyPress(CONFIRM)) {
			if(index == 0)
				GameData::UP_MOV = enteredKey;
			else if(index == 1)
				GameData::DOWN_MOV = enteredKey;
			else if(index == 2)
				GameData::LEFT_MOV = enteredKey;
			else if(index == 3)
				GameData::RIGHT_MOV = enteredKey;
			else if(index == 4)
				GameData::MAGIC_BUBBLES = enteredKey;
			else if(index == 5)
				GameData::MAGIC_FIREBALL = enteredKey;
			else if(index == 6)
				GameData::MAGIC_CAPTURE = enteredKey;
			else if(index == 7)
				GameData::PAUSE = enteredKey;

			if(!buttons["keys"][index].expired()) {
				Button* b = (Button*) buttons["keys"][index].lock()->GetComponent("Button");
				if(b) {
					b->SetColor(SDL_Color {});
				}
			}

			waitingKey = false;
			waitingConfirmation = false;
		}
		else if(GameData::key != enteredKey) {
			waitingConfirmation = false;
		}
	}
}

void TitleState::Navigate() {
	if(InputManager::GetToggle()) {
		bool shouldBreak = false;

		for(auto& i: buttons) {
			if(i.first != "selected" && i.first != "keys") {
				for(unsigned int j = 0; j < i.second.size(); j++) {
					if(!i.second[j].expired()) {
						if(i.second[j].lock()->IsActive()) {
							Button* b = (Button*) i.second[j].lock()->GetComponent("Button");
							if(b) {
								if(b->Selected()) {
									shouldBreak = true;
									layer = i.first;
									index = j;
									break;
								}
							}
						}
					}
				}
			}
			if(shouldBreak) {
				break;
			}
		}
	}
	else {
		if(InputManager::KeyPress(SDLK_UP) || InputManager::KeyPress(GameData::UP_MOV)) {
			index--;
			if(index < 0)
				index = buttons[layer].size()-1;
		}
		else if(InputManager::KeyPress(SDLK_DOWN) || InputManager::KeyPress(GameData::DOWN_MOV)) {
			index++;
			if(index > buttons[layer].size()-1)
				index = 0;
		}
		else if(InputManager::KeyPress(SDLK_LEFT) || InputManager::KeyPress(GameData::LEFT_MOV)) {
			if(layer == "stage")
				layer = "main";
			else if(layer == "controls" || layer == "screen")
				layer = "settings";

			if(index > buttons[layer].size()-1)
				index = buttons[layer].size()-1;
		}
		else if(InputManager::KeyPress(SDLK_RIGHT) || InputManager::KeyPress(GameData::RIGHT_MOV)) {
			if(layer == "main") {
				if(!buttons["stage"][0].expired())
					if(buttons["stage"][0].lock()->IsActive())
						layer = "stage";
			}
			else if(layer == "settings") {
				if(!buttons["controls"][0].expired())
					if(buttons["controls"][0].lock()->IsActive())
						layer = "controls";
				if(!buttons["screen"][0].expired())
					if(buttons["screen"][0].lock()->IsActive())
						layer = "screen";
			}

			if(index > buttons[layer].size()-1)
				index = buttons[layer].size()-1;
		}
	}
}

void TitleState::ExecuteButton() {
	if(layer == "main") {
		if(index == 0) {
			for(unsigned int i = 0; i < buttons["stage"].size(); i++)
				if(!buttons["stage"][i].expired())
					buttons["stage"][i].lock()->Activate();

			layer = "stage";
			index = 0;
		}
		else if(index == 1) {
			for(unsigned int i = 0; i < buttons["main"].size(); i++)
				if(!buttons["main"][i].expired())
					buttons["main"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["stage"].size(); i++)
				if(!buttons["stage"][i].expired())
					buttons["stage"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["selected"].size(); i++)
				if(!buttons["selected"][i].expired())
					buttons["selected"][i].lock()->Deactivate();

			animationCount = 9;
			layer = "settings";
			index = 0;
		}
		else if(index == 2) {
			animationCount = 13;
		}
	}
	else if(layer == "stage") {
		animationCount = 13;
	}
	else if(layer == "settings") {
		if(index == 0) {
			for(unsigned int i = 0; i < buttons["screen"].size(); i++)
				if(!buttons["screen"][i].expired())
					buttons["screen"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["controls"].size(); i++)
				if(!buttons["controls"][i].expired())
					buttons["controls"][i].lock()->Activate();

			for(unsigned int i = 0; i < buttons["keys"].size(); i++)
				if(!buttons["keys"][i].expired())
					buttons["keys"][i].lock()->Activate();

			layer = "controls";
			index = 0;
		}
		else if(index == 1) {
			for(unsigned int i = 0; i < buttons["controls"].size(); i++)
				if(!buttons["controls"][i].expired())
					buttons["controls"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["keys"].size(); i++)
				if(!buttons["keys"][i].expired())
					buttons["keys"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["screen"].size(); i++)
				if(!buttons["screen"][i].expired())
					buttons["screen"][i].lock()->Activate();

			layer = "screen";
			index = 0;
		}
		else if(index == 2) {
			for(unsigned int i = 0; i < buttons["settings"].size(); i++)
				if(!buttons["settings"][i].expired())
					buttons["settings"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["controls"].size(); i++)
				if(!buttons["controls"][i].expired())
					buttons["controls"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["keys"].size(); i++)
				if(!buttons["keys"][i].expired())
					buttons["keys"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["screen"].size(); i++)
				if(!buttons["screen"][i].expired())
					buttons["screen"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["selected"].size(); i++)
				if(!buttons["selected"][i].expired())
					buttons["selected"][i].lock()->Deactivate();

			animationCount = 9;
			layer = "main";
			index = 0;
		}
	}
	else if(layer == "controls") {
		if(!buttons["keys"][index].expired()) {
			Button* b = (Button*) buttons["keys"][index].lock()->GetComponent("Button");
			if(b) {
				if(!b->GetText().expired()) {
					Vec2 size = b->GetText().lock()->box.GetSize();

					b->SetText("NEW KEY");
					b->SetColor(SDL_Color {255, 0, 0, 0});

					CameraFollower* cf = (CameraFollower*) b->GetText().lock()->GetComponent("CameraFollower");
					if(cf) {
						cf->SetTruePos(cf->GetTruePos() + size/2 - b->GetText().lock()->box.GetSize()/2);
					}
				}
			}
		}

		waitingKey = true;
	}
	else if(layer == "screen") {
		if(index == 0) {
			Game::GetInstance().Fullscreen(GameData::fullscreen);
			GameData::fullscreen = !GameData::fullscreen;
		}
	}
}

void TitleState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(animationCount < 9) {
		animationT.Update(dt);
		
		UpdateArray(dt, "BOOK");
		UpdateArray(dt, "PASS");
		UpdateArray(dt, "PAGES");
		UpdateArray(dt, "TITLE1");
		UpdateArray(dt, "TITLE2");
		UpdateArray(dt, "PRESS");

		Opening();
	}
	else if(animationCount < 13){
		animationT.Update(dt);

		UpdateArray(dt, "PASS");
		UpdateArray(dt, "PAGES");

		Passing();
	}
	else if(animationCount < 16) {
		animationT.Update(dt);

		UpdateArray(dt, "BOOK");
		UpdateArray(dt, "PASS");
		UpdateArray(dt, "PAGES");

		Closing();
	}
	else {
		UpdateArray(dt, "PASS");
		UpdateArray(dt, "PAGES");
		UpdateArray(dt, "MAIN");
		UpdateArray(dt, "MISC");
		UpdateArray(dt, "HUD");

		if(!waitingKey) {
			Navigate();

			if(!buttons[layer][index].expired()) {
				Rect box = buttons[layer][index].lock()->box;
				if(!buttons["selected"][0].expired())
					buttons["selected"][0].lock()->box.SetCenter(box.GetCenter()-Vec2(box.w/2+15, 0));
				if(!buttons["selected"][1].expired())
					buttons["selected"][1].lock()->box.SetCenter(box.GetCenter()+Vec2(box.w/2+15, 0));

				Button* b = (Button*) buttons[layer][index].lock()->GetComponent("Button");
				if(b->Clicked())
					ExecuteButton();
			}
		}
		else {
			SetKey();
		}
	}
}

void TitleState::Render() {
	if(animationCount < 9) {
		RenderArray("BOOK");
		RenderArray("PASS");
		RenderArray("PAGES");
		RenderArray("TITLE1");
		RenderArray("TITLE2");
		RenderArray("PRESS");
	}
	else if(animationCount < 13) {
		RenderArray("PASS");
		RenderArray("PAGES");
	}
	else if(animationCount < 16) {
		RenderArray("BOOK");
		RenderArray("PASS");
		RenderArray("PAGES");
	}
	else {
		RenderArray("PASS");
		RenderArray("PAGES");
		RenderArray("MAIN");
		RenderArray("MISC");
		RenderArray("HUD");

	}
}
