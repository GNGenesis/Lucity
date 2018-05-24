#include "NPC.h"
#include "Game.h"
#include "GameData.h"

#include <math.h>

NPC::NPC(GameObject& associated, Personality p) : Character(associated, p.GetName()) {
	SetHealth(2);
	SetAction(IDLE);
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
			SetSpeed(person.GetSpeed().x);
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
	if(associated.box.x+associated.box.w > GameData::screenSize.x)
		associated.box.x = GameData::screenSize.x-associated.box.w;
	if(associated.box.y < 0)
		associated.box.y = 0;
	if(associated.box.y+associated.box.h > GameData::screenSize.y)
		associated.box.y = GameData::screenSize.y-associated.box.h;
}

void NPC::NotifyCollision(GameObject& other) {
	Character* character = (Character*) other.GetComponent("Character");
	if(character) {
		if(character->GetAction() == ATTACK) {
			if(damageT.Get() > damageCD) {
				Damage(1);
					actionT.Restart();
					offsetT = pow(-1,rand()%2)*(rand()%51)/100;
					damageT.Restart();
					SetAction("panic");
					SetSpeed(person.GetSpeed().y);
					SetAngleDirection(other.box.GetCenter().GetAngle(associated.box.GetCenter()));
			}
		}
	}
}

bool NPC::Is(std::string type) {
	return (type == "NPC" || Character::Is(type));
}

void NPC::SetAngleDirection(int angle) {
	Character::SetAngleDirection(angle);
	if(GetAngleDirection() >= 0 && GetAngleDirection() < 90)
		SetDirection("SE");
	else if(GetAngleDirection() >= 90 && GetAngleDirection() < 180)
		SetDirection("SW");
	else if(GetAngleDirection() >= 180 && GetAngleDirection() < 270)
		SetDirection("NW");
	else if(GetAngleDirection() >= 270 && GetAngleDirection() < 360)
		SetDirection("NE");
}
