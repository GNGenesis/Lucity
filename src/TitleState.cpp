#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"

#include "StageState.h"

#include "Sprite.h"
#include "Text.h"
#include "CameraFollower.h"

TitleState::TitleState() : State() {
	GameObject* go;

	//Background
	go = new GameObject();
	go->AddComponent(new Sprite(*go, "assets/img/title.jpg"));
	go->AddComponent(new CameraFollower(*go));
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	//Text
	go = new GameObject();
	go->AddComponent(new Text(*go, "assets/font/Call me maybe.ttf", 72, "PRESS SPACE TO CONTINUE", SDL_Color {}, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, Vec2(512, 500)-(go->box.GetSize()/2)));
	AddObject(go, "GUI");
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

}

void TitleState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	if(InputManager::KeyPress(SPACE_KEY))
		Game::GetInstance().Push(new StageState());

	UpdateArray(dt, "BG");
	//UpdateArray(dt, "MAIN");
	UpdateArray(dt, "GUI");
}

void TitleState::Render() {
	RenderArray("BG");
	//RenderArray("MAIN");
	RenderArray("GUI");
}
