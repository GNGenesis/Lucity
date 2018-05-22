#include "Player.h"
#include "Game.h"
#include "InputManager.h"

#include "Animator.h"
#include "Collider.h"
#include "Compass.h"

Player::Player(GameObject& associated, int n) : Character(associated) {
	SetHealth(5);
	SetSpeed(200);
	pNumber = n;
	directionAngle = 0;
	associated.AddComponent(new Animator(associated, this, "lucas"));
	associated.AddComponent(new Collider(associated));
}

Player::~Player() {

}

void Player::Start() {
	GameObject* go = new GameObject();
	char n[3];
	sprintf(n, "%d", pNumber+1);
	go->AddComponent(new Compass(*go, associated, n));
	Game::GetInstance().GetCurrentState().AddObject(go);
}

void Player::Update(float dt) {
	SetAngleDirection(dt);
	
	if(directionAngle > 360)
		directionAngle -= 360;
	else if(directionAngle < 0)
		directionAngle += 360;

	if(directionAngle >= 0 && directionAngle < 90)
		SetDirection("SE");
	else if(directionAngle >= 90 && directionAngle < 180)
		SetDirection("SW");
	else if(directionAngle >= 180 && directionAngle < 270)
		SetDirection("NW");
	else if(directionAngle >= 270 && directionAngle < 360)
		SetDirection("NE");

	if(Attacking()) {
		SetAction("attack");
	}
	else if(Walking()) {
		SetAction("walk");
		Vec2 mov = Vec2(Vec2::Cos(directionAngle), Vec2::Sin(directionAngle))*GetSpeed()*dt;
		associated.box.SetCenter(associated.box.GetCenter()+mov);
	}
	else{
		SetAction("idle");
	}
}

bool Player::Is(std::string type) {
	return (type == "Player" || Character::Is(type));
}

bool Player::Attacking() {
	if(InputManager::GetJoystick(pNumber))
		return (InputManager::IsJButtonDown(pNumber, 2));
	else if(pNumber == 0)
		return InputManager::IsMouseDown(RIGHT_MOUSE_BUTTON);
	else if(pNumber == 1)
		return InputManager::IsKeyDown(SDLK_e);
	else if(pNumber == 2)
		return InputManager::IsKeyDown(SDLK_o);
	else if(pNumber == 3)
		return InputManager::IsKeyDown(SDLK_RSHIFT);
	else	
		return false;
}

bool Player::Walking() {
	if(InputManager::GetJoystick(pNumber))
		return (InputManager::JoyAxisEvent(pNumber));
	else if(pNumber == 0)
		return InputManager::IsMouseDown(LEFT_MOUSE_BUTTON);
	else if(pNumber == 1)
		return InputManager::IsKeyDown(SDLK_w);
	else if(pNumber == 2)
		return InputManager::IsKeyDown(SDLK_i);
	else if(pNumber == 3)
		return InputManager::IsKeyDown(SDLK_UP);
	else	
		return false;
}

void Player::SetAngleDirection(float dt) {
	if(InputManager::GetJoystick(pNumber)) {
		directionAngle = InputManager::JoyAxisAngle(0);
	}
	else if(pNumber == 0) {
		directionAngle = associated.box.GetCenter().GetAngle(InputManager::GetMousePos());
	}
	else if(pNumber == 1) {
		if(InputManager::IsKeyDown(SDLK_a))
			directionAngle -= 120*dt;
		else if(InputManager::IsKeyDown(SDLK_d))
			directionAngle += 120*dt;
	}
	else if(pNumber == 2) {
		if(InputManager::IsKeyDown(SDLK_j))
			directionAngle -= 120*dt;
		else if(InputManager::IsKeyDown(SDLK_l))
			directionAngle += 120*dt;
	}
	else if(pNumber == 3) {
		if(InputManager::IsKeyDown(SDLK_LEFT))
			directionAngle -= 120*dt;
		else if(InputManager::IsKeyDown(SDLK_RIGHT))
			directionAngle += 120*dt;
	}
}

float Player::GetAngleDirection() {
	return directionAngle;
}
