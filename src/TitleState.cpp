#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"

#include "StageState.h"

#include "Sprite.h"
#include "Text.h"
#include "CameraFollower.h"

TitleState::TitleState() : State() {
	bg = new GameObject();
	txt = new GameObject();

	//Background
	bg->AddComponent(new Sprite(*bg, "assets/img/title.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box.SetSize(Vec2());

	//Text
	txt->AddComponent(new Text(*txt, "assets/font/Call me maybe.ttf", 72, 
							   "PRESS SPACE TO CONTINUE", SDL_Color {}, Text::SOLID));
	txt->AddComponent(new CameraFollower(*txt, Vec2(512, 500)-(txt->box.GetSize()/2)));
}

TitleState::~TitleState() {
	delete bg;
	delete txt;
}

void TitleState::LoadAssets() {

}

void TitleState::Start() {
	LoadAssets();
	bg->Start();
	txt->Start();
	StartArray();
	started = true;
}

void TitleState::Pause() {

}

void TitleState::Resume() {

}

void TitleState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	if(InputManager::KeyPress(SPACE_KEY))
		Game::GetInstance().Push(new StageState());

	toggleText.Update(dt);
	if(toggleText.Get() > 0.5) {
		if(txt->IsActive())
			txt->Deactivate();
		else
			txt->Activate();
		toggleText.Restart();
	}
	if(bg->IsActive())
		bg->Update(dt);
	if(txt->IsActive())
		txt->Update(dt);
	UpdateArray(dt);
}

void TitleState::Render() {
	if(bg->IsActive())
		bg->Render();
	if(txt->IsActive())
		txt->Render();
	RenderArray();
}
