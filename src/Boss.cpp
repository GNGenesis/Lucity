#include "Boss.h"
#include "Game.h"
#include "GameData.h"
#include "Camera.h"

#include "Attack.h"

#include <math.h>

Boss::Boss(GameObject& associated, Personality p) : NPC(associated, p) {
	SetHealth(6);
	rawr = false;
	mIdleT = 0.5;
	mWalkT = 0.5;
	mAttackT = 0.64;
	mDamageCD = 0.5;
	attacked = false;

	GameData::nMonsters++;
	GameData::nCivilians--;
}

Boss::~Boss() {
	GameData::nMonsters--;
	GameData::nCivilians++;
}

void Boss::Damage(int damage) {
	SetHealth(GetHealth()-damage);
	if (GetHealth() < 6) {
		rawr = true;
		initPos = associated.box.GetCenter();
	}
	if(GetHealth() < 1)
		associated.RequestDelete();
}

void Boss::Update(float dt) {
	if(!rawr) {
		NPC::Update(dt);
	}
	else {
		mActionT.Update(dt);
		mDamageT.Update(dt);
		if(GetAction() == "bIdle") {
			if(mActionT.Get() > mIdleT+mOffsetT) {
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				if (rand()%2) {
					SetAction("bWalk");
				} else {
					SetAction("bAttack");
				}
				SetSpeed(150);
			}
		}
		else if(GetAction() == "bWalk") {
			if(mActionT.Get() > mWalkT+mOffsetT) {
				NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(initPos) - 45 + rand()%91);
				mActionT.Restart();
				mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
				if (rand()%2) {
					SetAction("bAttack");
				} else {
					SetAction("bIdle");
				}
			}
			else {
				if(!GameData::player.expired()) {
					associated.box.SetCenter(associated.box.GetCenter()+Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt);
				}
			}
		}
		else if (GetAction() == "bHurt") {
			if(!GameData::player.expired()) {
				NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
				do {
					initPos = Vec2::Project(20, rand()%361);
				} while (initPos.x < 0 ||
								 initPos.y < 0 ||
								 initPos.x + associated.box.w > GameData::mapSize.x ||
								 initPos.y + associated.box.h > GameData::mapSize.y);
			}
		}
		else if (GetAction() == "bAttack") {
			if(!GameData::player.expired()) {
				if(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()) >= 0 &&
				   associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()) < 90)
					SetDirection("SE");
				else if(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()) >= 90 &&
				        associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()) < 180)
					SetDirection("SW");
				else if(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()) >= 180 &&
				        associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()) < 270)
					SetDirection("NW");
				else if(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()) >= 270 &&
				        associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()) < 360)
					SetDirection("NE");
				NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
			}
			if (!attacked && mActionT.Get() > mAttackT/2) {
				GameObject* go = new GameObject();
				go->AddComponent(new Attack(*go, associated, Attack::PROJECTED, 4, 0, associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()), 300));
				Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
				attacked = false;
			}
			if(mActionT.Get() > mAttackT) {
				attacked = false;
				mActionT.Restart();
				if (rand()%2) {
					SetAction("bIdle");
				} else {
					SetAction("bWalk");
				}
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

void Boss::NotifyCollision(GameObject& other) {
	if(!rawr) {
		NPC::NotifyCollision(other);
		if(rawr) {
			SetAction("bIdle");
		}
	}
	else {
		Attack* attack = (Attack*) other.GetComponent("Attack");
		if(attack) {
			if(!attack->IsOwner(associated)) {
				if(!attack->IsAlly("Boss")) {
					if(mDamageT.Get() > mDamageCD) {
						SetAction("bHurt");
						Damage(1);
						mDamageT.Restart();
						mOffsetT = pow(-1,rand()%2)*(rand()%51)/100;
					}
				}
			}
		}
	}
}

bool Boss::Is(std::string type) {
	return (type == "Boss" || NPC::Is(type));
}
