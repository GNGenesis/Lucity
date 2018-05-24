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
		/*if(InputManager::IsKeyDown(UP_ARROW_KEY))
			pos.y -= speed.y*dt;
		if(InputManager::IsKeyDown(DOWN_ARROW_KEY))
			pos.y += speed.y*dt;
		if(InputManager::IsKeyDown(LEFT_ARROW_KEY))
			pos.x -= speed.x*dt;
		if(InputManager::IsKeyDown(RIGHT_ARROW_KEY))
			pos.x += speed.x*dt;*/
	}else{
		pos.x = focus->box.GetCenter().x-GameData::screenSize.x/2;
		pos.y = focus->box.GetCenter().y-GameData::screenSize.y/2;
	}
}

GameObject* Camera::GetFocus() {
	return focus;
}
