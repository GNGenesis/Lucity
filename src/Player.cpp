#include "Player.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"

#include "Compass.h"

Player::Player(GameObject& associated, std::string name, int n) : Character(associated, name) {
	SetHealth(5);
	SetSpeed(200);
	pNumber = n;
}

Player::~Player() {

}

void Player::Start() {
	GameObject* go = new GameObject();
	char n[3];
	sprintf(n, "%d", pNumber+1);
	go->AddComponent(new Compass(*go, associated, n));
	Game::GetInstance().GetCurrentState().AddObject(go, "GUI");
}

void Player::Update(float dt) {
	SetAngleDirection(dt);
	
	if(GetAngleDirection() > 360)
		Character::SetAngleDirection(GetAngleDirection()-360);
	else if(GetAngleDirection() < 0)
		Character::SetAngleDirection(GetAngleDirection()+360);

	if(GetAngleDirection() >= 0 && GetAngleDirection() < 90)
		SetDirection("SE");
	else if(GetAngleDirection() >= 90 && GetAngleDirection() < 180)
		SetDirection("SW");
	else if(GetAngleDirection() >= 180 && GetAngleDirection() < 270)
		SetDirection("NW");
	else if(GetAngleDirection() >= 270 && GetAngleDirection() < 360)
		SetDirection("NE");

	if(Attacking()) {
		SetAction("attack");
	}
	else if(Walking()) {
		SetAction("walk");
		Vec2 mov = Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt;
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
		Character::SetAngleDirection(InputManager::JoyAxisAngle(pNumber));
	}
	else if(pNumber == 0) {
		Character::SetAngleDirection(associated.box.GetCenter().GetAngle(InputManager::GetMousePos()));
	}
	else if(pNumber == 1) {
		if(InputManager::IsKeyDown(SDLK_a))
			Character::SetAngleDirection(GetAngleDirection()-120*dt);
		else if(InputManager::IsKeyDown(SDLK_d))
			Character::SetAngleDirection(GetAngleDirection()+120*dt);
	}
	else if(pNumber == 2) {
		if(InputManager::IsKeyDown(SDLK_j))
			Character::SetAngleDirection(GetAngleDirection()-120*dt);
		else if(InputManager::IsKeyDown(SDLK_l))
			Character::SetAngleDirection(GetAngleDirection()+120*dt);
	}
	else if(pNumber == 3) {
		if(InputManager::IsKeyDown(SDLK_LEFT))
			Character::SetAngleDirection(GetAngleDirection()-120*dt);
		else if(InputManager::IsKeyDown(SDLK_RIGHT))
			Character::SetAngleDirection(GetAngleDirection()+120*dt);
	}
}
