#include "EndState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"

#include "StageState.h"

#include "Sprite.h"
#include "Text.h"
#include "CameraFollower.h"

EndState::EndState() : State() {
	bg = new GameObject();
	txt = new GameObject();

	if(GameData::playerVictory) {
		bg->AddComponent(new Sprite(*bg, "assets/img/win.jpg"));
		bg->AddComponent(new CameraFollower(*bg));
		bg->box.SetSize(Vec2());

		txt->AddComponent(new Text(*txt, "assets/font/Call me maybe.ttf", 72, 
								   "PRESS SPACE TO TRY AGAIN", SDL_Color {}, Text::SOLID));
		txt->AddComponent(new CameraFollower(*txt, Vec2(512, 500)-(txt->box.GetSize()/2)));

		backgroundMusic = Music("assets/audio/endStateWin.ogg");
	}else{
		bg->AddComponent(new Sprite(*bg, "assets/img/lose.jpg"));
		bg->AddComponent(new CameraFollower(*bg));
		bg->box.SetSize(Vec2());

		txt->AddComponent(new Text(*txt, "assets/font/Call me maybe.ttf", 72, 
								   "PRESS SPACE TO TRY AGAIN", SDL_Color {255, 255, 255, 0}, Text::SOLID));
		txt->AddComponent(new CameraFollower(*txt, Vec2(512, 100)-(txt->box.GetSize()/2)));

		backgroundMusic = Music("assets/audio/endStateLose.ogg");
	}
}

EndState::~EndState() {
	delete bg;
	delete txt;
}

void EndState::LoadAssets() {

}

void EndState::Start() {
	LoadAssets();
	bg->Start();
	txt->Start();
	StartArray();
	backgroundMusic.Play();
	started = true;
}

void EndState::Pause() {

}

void EndState::Resume() {

}

void EndState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	if(InputManager::KeyPress(SPACE_KEY))
		popRequested = true;

	if(bg->IsActive())
		bg->Update(dt);
	if(txt->IsActive())
		txt->Update(dt);
	UpdateArray(dt);
}

void EndState::Render() {
	if(bg->IsActive())
		bg->Render();
	if(txt->IsActive())
		txt->Render();
	RenderArray();
}
