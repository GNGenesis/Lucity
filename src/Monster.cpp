#include "Monster.h"
#include "Game.h"
#include "GameData.h"
#include "Camera.h"

#include "Sprite.h"
#include "Attack.h"
#include "HP.h"

#include <math.h>

Monster::Monster(GameObject& associated, Personality p) : NPC(associated, p) {
	transformed = false;
	mIdleT = 2;
	mWalkT = 3;
	mAttackT = 1;
	mStunT = 1.5;
	mDamageCD = 0.5;
}

Monster::~Monster() {

}

void Monster::Transform() {
	transformed = true;
	SetAction("mTransform");
	SetDirection("");
	associated.AddComponent(new HP(associated, 2));
}

void Monster::Damage(int damage) {
	SetHealth(GetHealth()-damage);
	if(!transformed && damage > 0)
		Transform();
}

void Monster::Update(float dt) {
	if(!GameData::paused) {
		if(!transformed) {
			NPC::Update(dt);
		}
		else {
			mActionT.Update(dt);
			mDamageT.Update(dt);
			if(GetAction() == "mTransform") {
				if(mActionT.Get() > 0.84) {
					mActionT.Restart();
					mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
					SetAction("mIdle");
					SetDirection("SE");

					for(int i = 0; i < 6; i++) {
						GameObject* go = new GameObject();
						go->AddComponent(new Attack(*go, "Monster", "shockwave", associated.box.GetCenter()+Vec2(0, associated.box.h/2), 1, GetAngleDirection()+i*360/6, 50, 1, true));
						Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
						Camera::tremorT.Restart();
					}
				}
			}
			else if(GetAction() == "mStun") {
				if(mActionT.Get() > mStunT) {
					mActionT.Restart();
					mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
					SetAction("mAttack");
					SetDirection("SE");
					SetHealth(2);
				}
			}
			else if(GetHealth() < 1) {
				mActionT.Restart();
				SetAction("mStun");
				SetDirection("");
			}
			else if(GetAction() == "mIdle") {
				if(mActionT.Get() > mIdleT + mOffsetT) {
					mActionT.Restart();
					mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
					SetAction("mWalk");
					SetSpeed(150);
					NPC::SetAngleDirection(rand()%360);
				}
			}
			else if(GetAction() == "mWalk") {
				if(mActionT.Get() > mWalkT + mOffsetT) {
					mActionT.Restart();
					mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
					if(!GameData::player.expired())
						SetAction("mAttack");
					else
						SetAction("mIdle");
				}
				else {
					if(!GameData::player.expired())
						NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
					associated.box.SetCenter(associated.box.GetCenter()+Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt);
				}
			}
			else if(GetAction() == "mAttack") {
				if(mActionT.Get() > mAttackT) {
					mActionT.Restart();
					mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
					SetAction("mIdle");

					for(int i = 0; i < 6; i++) {
						GameObject* go = new GameObject();
						go->AddComponent(new Attack(*go, "Monster", "shockwave", associated.box.GetCenter()+Vec2(0, associated.box.h/2), 1, GetAngleDirection()+i*360/6, 50, 1, true));
						Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
						Camera::tremorT.Restart();
					}
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
	}
}

void Monster::NotifyCollision(GameObject& other) {
	if(!transformed) {
		NPC::NotifyCollision(other);
	}
	else {
		Attack* attack = (Attack*) other.GetComponent("Attack");
		if(attack) {
			if(!attack->IsAlly("Monster")) {
				if(GetAction() != "mStun" && GetAction() != "mTransform") {
					if(attack->GetDamage() > 0) {
						if(mDamageT.Get() > mDamageCD) {
							Damage(attack->GetDamage());
							mDamageT.Restart();
						}
					}
				}
				else if(GetAction() == "mStun") {
					if(attack->GetDamage() == 0) {
						associated.RequestDelete();
						GameObject* go = new GameObject();
						go->AddComponent(new Sprite(*go, "assets/img/characters/monster/capture.png", 7, 0.12, false, 0.84));
						go->box.SetCenter(Vec2(associated.box.x+associated.box.w/2, associated.box.y+associated.box.h-go->box.h/2));
						Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
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
