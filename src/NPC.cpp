#include "NPC.h"
#include "Game.h"
#include "GameData.h"

#include "AOE.h"
#include "Attack.h"
#include "Exclamation.h"

#include <math.h>

NPC::NPC(GameObject& associated, Personality p) : Character(associated, p.GetName()) {
	SetHealth(2);
	person = p;
	offsetT = pow(-1,rand()%2)*(rand()%51)/100;
	damageCD = 0.5;

	GameData::nCivilians++;
}

NPC::~NPC() {
	GameData::nCivilians--;
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
	Attack* attack = (Attack*) other.GetComponent("Attack");
	if(attack) {
		if(!attack->IsOwner(associated)) {
			if(damageT.Get() > damageCD) {
					Damage(1);
					damageT.Restart();
					actionT.Restart();
					offsetT = pow(-1,rand()%2)*(rand()%51)/100;
					SetAction(PANIC);
					SetSpeed(person.GetPanicSpeed());
					SetAngleDirection(other.box.GetCenter().GetAngle(associated.box.GetCenter()));
			}
		}
	}

	AOE* aoe = (AOE*) other.GetComponent("AOE");
	if(aoe) {
		if(person.IsAfraid(aoe->GetOwnerName())) {
			if(GetAction() != PANIC) {
				actionT.Restart();
				offsetT = pow(-1,rand()%2)*(rand()%51)/100;
				scared = true;
				SetAction(SHOCK);
				SetAngleDirection(associated.box.GetCenter().GetAngle(other.box.GetCenter()));
				GameObject* go = new GameObject();
				go->AddComponent(new Exclamation(*go, associated));
				Game::GetInstance().GetCurrentState().AddObject(go, "MISC");
			}
		}

		if(person.IsInterested(aoe->GetOwnerName())) {
			if(GetAction() == IDLE) {
				actionT.Restart();
				offsetT = pow(-1,rand()%2)*(rand()%51)/100;
				scared = false;
				SetAction(SHOCK);
				SetAngleDirection(associated.box.GetCenter().GetAngle(other.box.GetCenter()));
				GameObject* go = new GameObject();
				go->AddComponent(new Exclamation(*go, associated));
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
