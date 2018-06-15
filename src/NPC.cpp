#include "NPC.h"
#include "Game.h"
#include "GameData.h"

#include "Sprite.h"
#include "FOV.h"
#include "Reaction.h"
#include "Attack.h"
#include "Monster.h"
#include "MainObject.h"

#include <math.h>

NPC::NPC(GameObject& associated, Personality p) : Character(associated, p.GetName()) {
	SetHealth(1);
	person = p;
	offsetT = pow(-1,rand()%2)*(rand()%51)/100;
	damageCD = 0.5;

	GameData::nCivilians++;
}

NPC::~NPC() {
	GameData::nCivilians--;
}

void NPC::Start() {
	GameObject* go = new GameObject();
	go->AddComponent(new FOV(*go, associated, 100));
	Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
}

void NPC::Update(float dt) {
	actionT.Update(dt);
	damageT.Update(dt);

	if(GetAction() == IDLE) {
		if(actionT.Get() > person.GetTime(IDLE)+offsetT) {
			actionT.Restart();
			offsetT = pow(-1,rand()%2)*(rand()%51)/100;
			SetAction(WALK);
			SetSpeed(person.GetNormalSpeed());
			SetAngleDirection(rand()%360);
		}
	}
	else if(GetAction() == WALK) {
		if(actionT.Get() > person.GetTime(WALK)+offsetT) {
			actionT.Restart();
			offsetT = pow(-1,rand()%2)*(rand()%51)/100;
			SetAction(IDLE);
		}else{
			associated.box.SetPos(associated.box.GetPos()+(Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt));
		}
	}
	else if(GetAction() == SHOCK) {
		if(actionT.Get() > person.GetTime(SHOCK)+offsetT) {
			actionT.Restart();
			offsetT = pow(-1,rand()%2)*(rand()%51)/100;
			if(scared) {
				SetAction(PANIC);
				SetSpeed(person.GetPanicSpeed());
				SetAngleDirection(GetAngleDirection()-180);

				GameObject* go = new GameObject();
				if(GetDirection() == "NE" || GetDirection() == "SE")
					go->AddComponent(new Sprite(*go, "assets/img/effects/dustE.png", 6, 0.05, false, 0.3));
				else if(GetDirection() == "NW" || GetDirection() == "SW")
					go->AddComponent(new Sprite(*go, "assets/img/effects/dustW.png", 6, 0.05, false, 0.3));
				go->box.SetCenter(associated.box.GetCenter()+(Vec2(Vec2::Cos(GetAngleDirection()+180), Vec2::Sin(GetAngleDirection()+180))*30));
				Game::GetInstance().GetCurrentState().AddObject(go, "EFFECT");
			}
			else {
				SetAction(WALK);
				SetSpeed(person.GetNormalSpeed());
				SetAngleDirection(rand()%360);
			}
		}
	}
	else if(GetAction() == PANIC) {
		if(actionT.Get() > person.GetTime(PANIC)+offsetT) {
			actionT.Restart();
			offsetT = pow(-1,rand()%2)*(rand()%51)/100;
			SetAction(IDLE);
		}else{
			associated.box.SetPos(associated.box.GetPos()+(Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt));
		}
	}

	if(associated.box.x < 0)
		associated.box.x = 0;
	if(associated.box.x+associated.box.w > GameData::mapSize.x)
		associated.box.x = GameData::mapSize.x-associated.box.w;
	if(associated.box.y < 0)
		associated.box.y = 0;
	if(associated.box.y+associated.box.h > GameData::mapSize.y)
		associated.box.y = GameData::mapSize.y-associated.box.h;
}

void NPC::NotifyCollision(GameObject& other) {
	
	if(other.GetComponent("Attack")) {
		Attack* attack = (Attack*) other.GetComponent("Attack");
		if(!attack->IsOwner(associated)) {
			Damage(1);
		}
	}
	else if(other.GetComponent("NPC")) {
		if(other.GetComponent("Monster")) {
			Monster* mon = (Monster*) other.GetComponent("Monster");
			if(mon->IsTransformed()) {
				if(GetAction() != PANIC && GetAction() != SHOCK) {
					actionT.Restart();
					offsetT = pow(-1,rand()%2)*(rand()%51)/100;
					scared = true;
					SetAction(SHOCK);
					SetAngleDirection(associated.box.GetCenter().GetAngle(other.box.GetCenter()));
					GameObject* go = new GameObject();
					go->AddComponent(new Reaction(*go, associated, "fear"));
					Game::GetInstance().GetCurrentState().AddObject(go, "MISC");
				}
			}
		}
		else {
			NPC* npc = (NPC*) other.GetComponent("NPC");
			if(person.IsAfraid(npc->GetName())) {
				if(GetAction() != PANIC && GetAction() != SHOCK) {
					actionT.Restart();
					offsetT = pow(-1,rand()%2)*(rand()%51)/100;
					scared = true;
					SetAction(SHOCK);
					SetAngleDirection(associated.box.GetCenter().GetAngle(other.box.GetCenter()));
					GameObject* go = new GameObject();
					go->AddComponent(new Reaction(*go, associated, "fear"));
					Game::GetInstance().GetCurrentState().AddObject(go, "MISC");
				}
			}
			else if(person.IsInterested(npc->GetName())) {
				if(GetAction() == IDLE) {
					actionT.Restart();
					offsetT = pow(-1,rand()%2)*(rand()%51)/100;
					scared = false;
					SetAction(SHOCK);
					SetAngleDirection(associated.box.GetCenter().GetAngle(other.box.GetCenter()));
					GameObject* go = new GameObject();
					go->AddComponent(new Reaction(*go, associated, "interest"));
					Game::GetInstance().GetCurrentState().AddObject(go, "MISC");
				}
			}
		}
	}
	else if(other.GetComponent("MainObject")) {
		MainObject* mo = (MainObject*) other.GetComponent("MainObject");
		if(person.IsAfraid(mo->GetName())) {
			if(GetAction() != PANIC && GetAction() != SHOCK) {
				actionT.Restart();
				offsetT = pow(-1,rand()%2)*(rand()%51)/100;
				scared = true;
				SetAction(SHOCK);
				SetAngleDirection(associated.box.GetCenter().GetAngle(other.box.GetCenter()));
				GameObject* go = new GameObject();
				go->AddComponent(new Reaction(*go, associated, "fear"));
				Game::GetInstance().GetCurrentState().AddObject(go, "MISC");
			}
		}
		else if(person.IsInterested(mo->GetName())) {
			if(GetAction() == IDLE) {
				actionT.Restart();
				offsetT = pow(-1,rand()%2)*(rand()%51)/100;
				scared = false;
				SetAction(SHOCK);
				SetAngleDirection(associated.box.GetCenter().GetAngle(other.box.GetCenter()));
				GameObject* go = new GameObject();
				go->AddComponent(new Reaction(*go, associated, "interest"));
				Game::GetInstance().GetCurrentState().AddObject(go, "MISC");
			}
		}
	}
}

bool NPC::Is(std::string type) {
	return (type == "NPC" || Character::Is(type));
}

void NPC::SetAngleDirection(int angle) {
	Character::SetAngleDirection(angle);
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
}

std::string NPC::GetName() {
	return person.GetName();
}
