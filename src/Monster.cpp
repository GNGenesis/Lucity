#include "Monster.h"
#include "Game.h"
#include "GameData.h"
#include "Camera.h"

#include "Attack.h"

#include <math.h>

Monster::Monster(GameObject& associated, Personality p) : NPC(associated, p) {
	SetHealth(3);
	rawr = false;
	mIdleT = 0.5;
	mWalkT = 2;
	mDamageCD = 0.5;

	GameData::nMonsters++;
	GameData::nCivilians--;
}

Monster::~Monster() {
	GameData::nMonsters--;
	GameData::nCivilians++;
}

void Monster::Damage(int damage) {
	SetHealth(GetHealth()-damage);
	rawr = true;
	if(GetHealth() < 1)
		associated.RequestDelete();
}

void Monster::Update(float dt) {
	if(!rawr) {
		NPC::Update(dt);
	}
	else {
		mActionT.Update(dt);
		mDamageT.Update(dt);
		if(GetAction() == "mIdle") {
			if(mActionT.Get() > mIdleT+mOffsetT) {
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				SetAction("mWalk");
				SetSpeed(150);
			}
		}
		else if(GetAction() == "mWalk") {
			if(mActionT.Get() > mWalkT+mOffsetT) {
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				SetAction("mIdle");
				
				GameObject* go = new GameObject();
				go->AddComponent(new Attack(*go, associated, Attack::CENTERED, 0.5, 50));
				Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
				Camera::tremorT.Restart();
			}
			else {
				if(!GameData::player.expired()) {
					NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
					associated.box.SetCenter(associated.box.GetCenter()+Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt);
				}
			}
		}
	}
}

void Monster::NotifyCollision(GameObject& other) {
	if(!rawr) {
		NPC::NotifyCollision(other);
		if(rawr) {
			SetAction("mIdle");
		}
	}
	else {
		Attack* attack = (Attack*) other.GetComponent("Attack");
		if(attack) {
			if(!attack->IsOwner(associated)) {
				if(!attack->IsAlly("Monster")) {
					if(mDamageT.Get() > mDamageCD) {
						Damage(1);
						mDamageT.Restart();
						mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
					}
				}
			}
		}
	}
}

bool Monster::Is(std::string type) {
	return (type == "Monster" || NPC::Is(type));
}
