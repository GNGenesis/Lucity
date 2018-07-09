#include "EndState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"

#include "Sprite.h"
#include "Text.h"
#include "CameraFollower.h"

EndState::EndState() : State() {
	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	Camera::pos = Vec2(0, 0);

	GameData::popAgain = false;

	GameObject* go;
	Sprite* sp;

	animationCount = 0;

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

		//Message
		go = new GameObject();
		if(GameData::playerVictory) {
			sp = new Sprite(*go, "assets/img/title/message_win.png", 2, 0.4);
			sp->SetScale(Vec2(3, 3));
			go->AddComponent(sp);
			go->AddComponent(new CameraFollower(*go, Vec2(275, 300) - (go->box.GetSize() / 2)));
		}
		else {
			sp = new Sprite(*go, "assets/img/title/message_loss.png", 2, 0.4);
			sp->SetScale(Vec2(3, 3));
			go->AddComponent(sp);
			go->AddComponent(new CameraFollower(*go, Vec2(275, 315) - (go->box.GetSize() / 2)));
		}
		AddObject(go, "MSG");
		go->box.SetPos(Vec2(-2000, -2000));
		go->Deactivate();

		//Gameplay Results
		
		//NPCs
		if(true) {
			char ch[3];
			sprintf(ch, "%d", GameData::nCivilians);
			std::string n = ch;
			std::string nc;
			std::string c = " civilians";
			if(GameData::nCivilians > 9)
				nc = std::string(n);
			else
				nc = "0" + std::string(n);
			std::string text = nc + c;

			go = new GameObject();
			sp = new Sprite(*go, "assets/img/characters/old/idleSW.png", 4, 0.2);
			go->AddComponent(sp);
			go->AddComponent(new CameraFollower(*go, Vec2(756-go->box.w/2, 100)));
			AddObject(go, "RESULTS");
			go->box.SetPos(Vec2(-2000, -2000));
			go->Deactivate();

			go = new GameObject();
			go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 30, text, SDL_Color {}, Text::SOLID));
			go->AddComponent(new CameraFollower(*go, Vec2(756-go->box.w/2, 125)));
			AddObject(go, "RESULTS");
			go->box.SetPos(Vec2(-2000, -2000));
			go->Deactivate();

			go = new GameObject();
			go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 30, "saved", SDL_Color {}, Text::SOLID));
			go->AddComponent(new CameraFollower(*go, Vec2(756-go->box.w/2, 165)));
			AddObject(go, "RESULTS");
			go->box.SetPos(Vec2(-2000, -2000));
			go->Deactivate();
		}

		//Monsters
		if(true) {
			char ch[3];
			sprintf(ch, "%d", GameData::nMaxMonsters-GameData::nMonsters);
			std::string n = ch;
			std::string nm;
			std::string m = " monsters";
			if(GameData::nMonsters > 9)
				nm = std::string(n);
			else
				nm = "0" + std::string(n);
			std::string text = nm + m;

			go = new GameObject();
			sp = new Sprite(*go, "assets/img/characters/monster/idleSW.png", 6, 0.2);
			go->AddComponent(sp);
			go->AddComponent(new CameraFollower(*go, Vec2(756-go->box.w/2, 215)));
			AddObject(go, "RESULTS");
			go->box.SetPos(Vec2(-2000, -2000));
			go->Deactivate();

			go = new GameObject();
			go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 30, text, SDL_Color {}, Text::SOLID));
			go->AddComponent(new CameraFollower(*go, Vec2(756-go->box.w/2, 255)));
			AddObject(go, "RESULTS");
			go->box.SetPos(Vec2(-2000, -2000));
			go->Deactivate();

			go = new GameObject();
			go->AddComponent(new Text(*go, "assets/font/Sabo-Filled.ttf", 30, "captured", SDL_Color {}, Text::SOLID));
			go->AddComponent(new CameraFollower(*go, Vec2(756-go->box.w/2, 295)));
			AddObject(go, "RESULTS");
			go->box.SetPos(Vec2(-2000, -2000));
			go->Deactivate();
		}

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
}

EndState::~EndState() {

}

void EndState::LoadAssets() {

}

void EndState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void EndState::Pause() {

}

void EndState::Resume() {
	int mw = 1024;
	int mh = 600;
	GameData::mapSize = Vec2(mw, mh);
	Camera::pos = Vec2(0, 0);

	GameData::popAgain = false;

	animationCount = 0;
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
	for(unsigned int i = 0; i < objects["MSG"].size(); i++) {
		Sprite* sp = (Sprite*) objects["MSG"][i]->GetComponent("Sprite");
		if(sp) {
			sp->SetFrame(0);
		}
	}
	for(unsigned int i = 0; i < objects["RESULTS"].size(); i++) {
		Sprite* sp = (Sprite*) objects["RESULTS"][i]->GetComponent("Sprite");
		if(sp) {
			sp->SetFrame(0);
		}
	}
}

void EndState::Opening() {
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
			for(unsigned int i = 0; i < objects["MSG"].size(); i++) {
				objects["MSG"][i]->Activate();
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 3) {
		if(animationT.Get() > 0.8) {
			animationCount++;
			for(unsigned int i = 0; i < objects["RESULTS"].size(); i++) {
				objects["RESULTS"][i]->Activate();
			}
			animationT.Restart();
		}
	}
	else if(animationCount == 4) {
		if(animationT.Get() > 0.35) {
			animationCount++;
			InputManager::ResetLastKey();
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
			for(unsigned int i = 0; i < objects["MSG"].size(); i++) {
				objects["MSG"][i]->Deactivate();
			}
			for(unsigned int i = 0; i < objects["RESULTS"].size(); i++) {
				objects["RESULTS"][i]->Deactivate();
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
				objects["PASS"][i]->Deactivate();
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
	else if(animationCount == 7) {
		if(animationT.Get() > 0.6) {
			popRequested = true;
			GameData::popAgain = true;
		}
	}
}

void EndState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	animationT.Update(dt);

	UpdateArray(dt, "BOOK");
	UpdateArray(dt, "PASS");
	UpdateArray(dt, "PAGES");
	UpdateArray(dt, "MSG");
	UpdateArray(dt, "RESULTS");
	UpdateArray(dt, "PRESS");

	Opening();
}

void EndState::Render() {
	RenderArray("BOOK");
	RenderArray("PASS");
	RenderArray("PAGES");
	RenderArray("MSG");
	RenderArray("RESULTS");
	RenderArray("PRESS");
}
