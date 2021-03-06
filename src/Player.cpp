#include "Player.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"

#include "Sprite.h"
#include "Attack.h"
#include "Book.h"
#include "Compass.h"
#include "HP.h"

Player::Player(GameObject& associated, std::string name, int n) : Character(associated, name) {
	SetHealth(5);
	associated.AddComponent(new HP(associated, 5));
	SetSpeed(200);
	pNumber = n;
	damageCD = 1;
}

Player::~Player() {

}

void Player::Start() {
	GameData::player = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated, "MAIN");

	GameObject* go = new GameObject();
	go->AddComponent(new Book(*go, associated));
	Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");

	go = new GameObject();
	char n[3];
	sprintf(n, "%d", pNumber+1);
	go->AddComponent(new Compass(*go, associated, n));
	Game::GetInstance().GetCurrentState().AddObject(go, "GUI");
}

void Player::Update(float dt) {
	if(!GameData::paused) {
		damageT.Update(dt);
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

		if(IsWalking()) {
			if(GetAction() != WALK) {
				GameObject* go = new GameObject();
				if(GetDirection() == "NE" || GetDirection() == "SE")
					go->AddComponent(new Sprite(*go, "assets/img/effects/dustE.png", 6, 0.05, false, 0.3));
				else if(GetDirection() == "NW" || GetDirection() == "SW")
					go->AddComponent(new Sprite(*go, "assets/img/effects/dustW.png", 6, 0.05, false, 0.3));
				go->box.SetCenter(associated.box.GetCenter()+(Vec2(Vec2::Cos(GetAngleDirection()+180), Vec2::Sin(GetAngleDirection()+180))*30));
				Game::GetInstance().GetCurrentState().AddObject(go, "EFFECT");
			}
			SetAction(WALK);
			Vec2 mov = Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt;
			associated.box.SetCenter(associated.box.GetCenter()+mov);
		}
		else if(IsWalkingBackwards()) {
			if(GetAction() != WALK) {
				GameObject* go = new GameObject();
				if(GetDirection() == "NE" || GetDirection() == "SE")
					go->AddComponent(new Sprite(*go, "assets/img/effects/dustW.png", 6, 0.05, false, 0.3));
				else if(GetDirection() == "NW" || GetDirection() == "SW")
					go->AddComponent(new Sprite(*go, "assets/img/effects/dustE.png", 6, 0.05, false, 0.3));
				go->box.SetCenter(associated.box.GetCenter()+(Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*30));
				Game::GetInstance().GetCurrentState().AddObject(go, "EFFECT");
			}
			SetAction(WALK);
			Vec2 mov = Vec2(Vec2::Cos(GetAngleDirection()+180), Vec2::Sin(GetAngleDirection()+180))*GetSpeed()*dt/2;
			associated.box.SetCenter(associated.box.GetCenter()+mov);
		}
		else {
			SetAction(IDLE);
		}
	}
	if (associated.box.x < 0)
		associated.box.x = 0;
	if (associated.box.x + associated.box.w > GameData::mapSize.x)
		associated.box.x = GameData::mapSize.x - associated.box.w;
	if (associated.box.y < GameData::upperLimit)
		associated.box.y = GameData::upperLimit;
	if (associated.box.y + associated.box.h > GameData::mapSize.y)
		associated.box.y = GameData::mapSize.y - associated.box.h;
}

void Player::NotifyCollision(GameObject& other) {
	Attack* attack = (Attack*) other.GetComponent("Attack");
	if(attack) {
		if(!attack->IsAlly("Player")) {
			if(damageT.Get() > damageCD) {
				Damage(attack->GetDamage());
				damageT.Restart();
			}
		}
	}
}

bool Player::Is(std::string type) {
	return (type == "Player" || Character::Is(type));
}

bool Player::IsWalking() {
	if(InputManager::IsMouseDown(LEFT_MOUSE_BUTTON))
		return true;
	else if(InputManager::IsKeyDown(GameData::UP_MOV))
		return true;
	else 
		return false;
}

bool Player::IsWalkingBackwards() {
	if(InputManager::IsKeyDown(GameData::DOWN_MOV))
		return true;
	else
		return false;
}

void Player::SetAngleDirection(float dt) {
	if(InputManager::IsKeyDown(GameData::LEFT_MOV))
		Character::SetAngleDirection(GetAngleDirection()-120*dt);
	else if(InputManager::IsKeyDown(GameData::RIGHT_MOV))
		Character::SetAngleDirection(GetAngleDirection()+120*dt);
	else if(InputManager::GetToggle())
		Character::SetAngleDirection(associated.box.GetCenter().GetAngle(InputManager::GetMousePos()));
}
