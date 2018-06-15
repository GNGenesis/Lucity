#include "Monster.h"
#include "Game.h"
#include "GameData.h"
#include "Camera.h"

#include "Sprite.h"
#include "Attack.h"

#include <math.h>

Monster::Monster(GameObject& associated, Personality p) : NPC(associated, p) {
	SetHealth(3);
	transformed = false;
	mIdleT = 0.5;
	mWalkT = 2;
	mAttackT = 0.48;
	mStunT = 3;
	mDamageCD = 0.5;

	GameData::nMonsters++;
	GameData::nCivilians--;
}

Monster::~Monster() {
	GameData::nMonsters--;
	GameData::nCivilians++;
}

void Monster::Transform() {
	transformed = true;
	SetAction("mTransform");
	SetDirection("");
}

void Monster::Damage(int damage) {
	SetHealth(GetHealth()-damage);
	if(!transformed)
		Transform();
	if(GetHealth() < 1)
		associated.RequestDelete();
		//SetAction("mStun");
}

void Monster::Update(float dt) {
	if(!transformed) {
		NPC::Update(dt);
	}
	else {
		mActionT.Update(dt);
		mDamageT.Update(dt);
		if(GetAction() == "mTransform") {
			if(mActionT.Get() > 1.4) {
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				SetAction("mIdle");
				SetDirection("SE");

				GameObject* go = new GameObject();
				go->AddComponent(new Attack(*go, associated, Attack::CENTERED, 0.5, 50));
				Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
				Camera::tremorT.Restart();
			}
		}
		else if(GetAction() == "mIdle") {
			if(mActionT.Get() > mIdleT + mOffsetT) {
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				SetAction("mWalk");
				SetSpeed(150);
			}
		}
		else if(GetAction() == "mWalk") {
			if(mActionT.Get() > mWalkT + mOffsetT) {
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				SetAction("mAttack");
			}
			else {
				if(!GameData::player.expired()) {
					NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
					associated.box.SetCenter(associated.box.GetCenter()+Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt);
				}
			}
		}
		else if(GetAction() == "mAttack") {
			if(mActionT.Get() > mAttackT) {
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				SetAction("mIdle");

				GameObject* go = new GameObject();
				go->AddComponent(new Attack(*go, associated, Attack::CENTERED, 0.5, 50));
				Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
				Camera::tremorT.Restart();

				go = new GameObject();
				go->AddComponent(new Sprite(*go, "assets/img/effects/crack.png", 4, 0.125, false, 0.5));
				go->box.SetCenter(Vec2(associated.box.x + associated.box.w/2, associated.box.y + associated.box.h));
				Game::GetInstance().GetCurrentState().AddObject(go, "EFFECT");
			}
		}
		else if(GetAction() == "mStun") {
			if(mActionT.Get() > mStunT) {
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				SetAction("mAttack");
				SetHP(2);
			}
		}
	}
}

void Monster::NotifyCollision(GameObject& other) {
	if(!transformed) {
		NPC::NotifyCollision(other);
	}
	else {
		Attack* attack = (Attack*) other.GetComponent("Attack");
		if(attack) {
			if(GetAction() != "mStun" && GetAction() != "mTransform") {
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
}

bool Monster::Is(std::string type) {
	return (type == "Monster" || NPC::Is(type));
}

bool Monster::IsTransformed() {
	return transformed;
}
