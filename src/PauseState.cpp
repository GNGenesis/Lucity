#include "PauseState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"

//#include "TutorialStageState.h"
#include "StageState.h"
//#include "BossStageState.h"

#include "Sprite.h"
#include "Text.h"
#include "Button.h"
#include "CameraFollower.h"

#include <algorithm>

PauseState::PauseState() : State() {
	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	Camera::pos = Vec2(0, 0);

	GameObject* go;
	Sprite* sp;

	animationCount = 0;
	layer = "main";
	index = 0;
	waitingKey = false;
	waitingConfirmation = false;

	//Opening Animations
	if(true) {
		//Opening Book
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/title/opening.png", 5, 0.1, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
		AddObject(go, "BOOK");

		//Pass Page Book
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/Title/passing.png", 6, 0.1, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
		AddObject(go, "PASS");

		//Page Left
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/Title/effect_left.png", 5, 0.15, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(275, 300) - (go->box.GetSize() / 2)));
		AddObject(go, "PAGES");
		go->Deactivate();

		//Page Right
		go = new GameObject();
		sp = new Sprite(*go, "assets/img/Title/effect_right.png", 5, 0.15, false);
		sp->SetScale(Vec2(4, 4));
		go->AddComponent(sp);
		go->AddComponent(new CameraFollower(*go, Vec2(750, 300) - (go->box.GetSize() / 2)));
		AddObject(go, "PAGES");
		go->Deactivate();
	}

	go = new GameObject();
	sp = new Sprite(*go, "assets/img/title/selector_left.png");
	sp->SetScale(Vec2(3, 3));
	go->AddComponent(sp);
	buttons["selected"].emplace_back(AddObject(go, "HUD"));
	go->Deactivate();

	go = new GameObject();
	sp = new Sprite(*go, "assets/img/title/selector_right.png");
	sp->SetScale(Vec2(3, 3));
	go->AddComponent(sp);
	buttons["selected"].emplace_back(AddObject(go, "HUD"));
	go->Deactivate();

	//Pause Menu: Main Menu
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Return to Main Menu", Vec2(275, 180)));
	buttons["main"].emplace_back(AddObject(go, "MAIN"));
	go->Deactivate();
	
	//Pause Menu: Settings
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Settings", Vec2(275, 220)));
	buttons["main"].emplace_back(AddObject(go, "MAIN"));
	go->Deactivate();
	
	//Pause Menu: Quit
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Quit", Vec2(275, 380)));
	buttons["main"].emplace_back(AddObject(go, "MAIN"));
	go->Deactivate();
	
	//Settings Menu: Controls
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Controls", Vec2(275, 180)));
	buttons["settings"].emplace_back(AddObject(go, "MAIN"));
	go->Deactivate();

	//Controls Menu
	if(true) {
		//Controls Menu: UP
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Up Movement Key", Vec2(695, 150)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: UP Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Up", Vec2(870, 150)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();
		
		//Controls Menu: DOWN
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Down Movement Key", Vec2(695, 190)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: DOWN Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Down", Vec2(870, 190)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();
		
		//Controls Menu: LEFT
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Left Movement Key", Vec2(695, 230)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: LEFT Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Left", Vec2(870, 230)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: RIGHT
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Right Movement Key", Vec2(695, 270)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: RIGHT Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Right", Vec2(870, 270)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: ACTION 1
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Attack 1 Key", Vec2(695, 310)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: ACTION 1 Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "1", Vec2(870, 310)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: ACTION 2
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Attack 2 Key", Vec2(695, 350)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: ACTION 2 Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "2", Vec2(870, 350)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: ACTION 3
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Attack 3 Key", Vec2(695, 390)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: ACTION 3 Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "3", Vec2(870, 390)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: PAUSE
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Pause Menu Key", Vec2(695, 430)));
		buttons["controls"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();

		//Controls Menu: ACTION 4 Key
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/keybind_button.png", "assets/font/VT323.ttf", "Escape", Vec2(870, 430)));
		buttons["keys"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();
	}

	//Settings Menu: Screen
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Screen", Vec2(275, 220)));
	buttons["settings"].emplace_back(AddObject(go, "MAIN"));
	go->Deactivate();

	//Screen Menu
	if(true) {
		//Screen Menu: fullscreen
		go = new GameObject();
		go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Fullsceen", Vec2(749, 180)));
		buttons["screen"].emplace_back(AddObject(go, "MAIN"));
		go->Deactivate();
	}
	
	//Settings Menu: Back
	go = new GameObject();
	go->AddComponentAsFirst(new Button(*go, "assets/img/title/button.png", "assets/font/VT323.ttf", "Back", Vec2(275, 380)));
	buttons["settings"].emplace_back(AddObject(go, "MAIN"));
	go->Deactivate();
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

}

void PauseState::Resume() {
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

void PauseState::Opening() {
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

void PauseState::Passing() {
	if(animationCount == 4) {
		animationCount++;
		for(unsigned int i = 0; i < objects["PAGES"].size(); i++) {
			Sprite* sp = (Sprite*) objects["PAGES"][i]->GetComponent("Sprite");
			if(sp) {
				sp->GoBack();
			}
		}
		animationT.Restart();
	}
	else if(animationCount == 5) {
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
	else if(animationCount == 6) {
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
	else if(animationCount == 7) {
		if(animationT.Get() > 0.75) {
			animationCount = 3;
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

void PauseState::SetKey() {
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

void PauseState::Navigate() {
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
			if(layer == "controls" || layer == "screen")
				layer = "settings";

			if(index > buttons[layer].size()-1)
				index = buttons[layer].size()-1;
		}
		else if(InputManager::KeyPress(SDLK_RIGHT) || InputManager::KeyPress(GameData::RIGHT_MOV)) {
			if(layer == "settings") {
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

void PauseState::ExecuteButton() {
	if(layer == "main") {
		if(index == 0) {
			popRequested = true;
			GameData::popAgain = true;
		}
		else if(index == 1) {
			for(unsigned int i = 0; i < buttons["main"].size(); i++)
				if(!buttons["main"][i].expired())
					buttons["main"][i].lock()->Deactivate();

			for(unsigned int i = 0; i < buttons["selected"].size(); i++)
				if(!buttons["selected"][i].expired())
					buttons["selected"][i].lock()->Deactivate();

			animationCount = 4;
			layer = "settings";
			index = 0;
		}
		else if(index == 2) {
			quitRequested = true;
		}
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

			animationCount = 4;
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

		}
		else if(index == 1) {

		}
	}
}

void PauseState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(animationCount < 3) {
		animationT.Update(dt);
		
		UpdateArray(dt, "BOOK");
		UpdateArray(dt, "PASS");
		UpdateArray(dt, "PAGES");

		Opening();
	}
	else if(animationCount < 4){
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
	else {
		animationT.Update(dt);

		UpdateArray(dt, "PASS");
		UpdateArray(dt, "PAGES");

		Passing();
	}
}

void PauseState::Render() {
	if(animationCount < 3) {
		RenderArray("BOOK");
		RenderArray("PASS");
		RenderArray("PAGES");
	}
	else if(animationCount < 4) {
		RenderArray("PASS");
		RenderArray("PAGES");
		RenderArray("MAIN");
		RenderArray("MISC");
		RenderArray("HUD");
	}
	else {
		RenderArray("PASS");
		RenderArray("PAGES");
	}
}
