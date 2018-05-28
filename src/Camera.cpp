#include "Camera.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2(300, 300);

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if(!focus) {
		if(InputManager::IsKeyDown(UP_ARROW_KEY))
			pos.y -= speed.y*dt;
		if(InputManager::IsKeyDown(DOWN_ARROW_KEY))
			pos.y += speed.y*dt;
		if(InputManager::IsKeyDown(LEFT_ARROW_KEY))
			pos.x -= speed.x*dt;
		if(InputManager::IsKeyDown(RIGHT_ARROW_KEY))
			pos.x += speed.x*dt;
	}else{
		int w, h;
		SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &w, &h);
		pos.x = focus->box.GetCenter().x-w/2;
		pos.y = focus->box.GetCenter().y-h/2;

		if(pos.x < 0)
			pos.x = 0;
		else if(pos.x > GameData::mapSize.x-w)
			pos.x = GameData::mapSize.x-w;
		if(pos.y < 0)
			pos.y = 0;
		else if(pos.y > GameData::mapSize.y-h)
			pos.y = GameData::mapSize.y-h;
	}
}

GameObject* Camera::GetFocus() {
	return focus;
}
