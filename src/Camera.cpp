#include "Camera.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"

#include <math.h>

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2(300, 300);
Timer Camera::tremorT = Timer();

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if(focus) {
		int w, h;
		SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &w, &h);
		pos = focus->box.GetCenter()-Vec2(w/2, h/2);

		if(pos.x < 0)
			pos.x = 0;
		else if(pos.x > GameData::mapSize.x-w)
			pos.x = GameData::mapSize.x-w;
		if(pos.y < 0)
			pos.y = 0;
		else if(pos.y > GameData::mapSize.y-h)
			pos.y = GameData::mapSize.y-h;

		tremorT.Update(dt);
		if(tremorT.Get() < 0.5)
			pos = pos+Vec2((int)(pow(-1, rand()%2)*(rand()%5)+1), (int)(pow(-1, rand()%2)*(rand()%5)+1));
	}
}

GameObject* Camera::GetFocus() {
	return focus;
}
