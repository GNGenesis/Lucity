#include "Camera.h"
#include "Game.h"
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
	}
}

GameObject* Camera::GetFocus() {
	return focus;
}
