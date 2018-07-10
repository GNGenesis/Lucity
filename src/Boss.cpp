#include "Boss.h"
#include "Game.h"
#include "GameData.h"
#include "Camera.h"

#include "Sprite.h"
#include "Attack.h"
#include "HP.h"
#include "Soul.h"

#include <math.h>

Boss::Boss(GameObject& associated, Personality p) : NPC(associated, p) {
	SetHealth(3);
	transformed = false;
	ramble = false;
	bIdleT = 2;
	bAttackT = 1;
	bStunT = 2.5;
	bHurtT = 2;
	bDamageCD = 3;
	move = false;
}

Boss::~Boss() {

}

void Boss::Transform() {
	transformed = true;
	SetHealth(6);
	SetSpeed(100);
	SetAction("bTransform");
	SetDirection("SE");
	anchor = associated.box.GetCenter();
	associated.AddComponent(new HP(associated, 6));
}

void Boss::Damage(int damage) {
	SetHealth(GetHealth()-damage);
	if(damage > 0) {
		bDamageT.Restart();
		if(!transformed) {
			if(GetHealth() > 0)
				ramble = true;
			else
				Transform();
		}
	}
}

void Boss::Update(float dt) {
	if(!GameData::paused) {	
		if(!transformed) {
			NPC::Update(dt);
			ramble = false;
		}
		else {
			bActionT.Update(dt);
			bSubActionT.Update(dt);
			bDamageT.Update(dt);
			if(GetAction() == "bTransform") {
				if(bActionT.Get() > 0.72) {
					bActionT.Restart();
					bOffsetT = (GameData::nMaxCivilians -GameData::nMaxCivilians)/30;
					SetAction("bIdle");
					SetDirection("SE");
				}
			}
			else if(GetAction() == "bStun") {
				if(bActionT.Get() > bStunT-bOffsetT) {
					bActionT.Restart();
					SetAction("bAttack");
					SetDirection("SE");
					SetHealth(3);
				}
			}
			else if(GetHealth() < 1) {
				bActionT.Restart();
				SetAction("bStun");
			}
			else if(GetAction() == "bHurt") {
				if(bActionT.Get() > bHurtT-bOffsetT) {
					bActionT.Restart();
					SetAction("bAttack");
					SetSpeed(50);
					anchor = associated.box.GetCenter();
					NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
				}
				else {
					associated.box.SetPos(associated.box.GetPos()+(Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt));
				}
				if(bSubActionT.Get() > 0.4) {
					bSubActionT.Restart();
					GameObject* go;
					int n = rand()%360;
					for(int i = 0; i < 8; i++) {
						go = new GameObject();
						go->AddComponent(new Attack(*go, "Boss", "energyball", associated.box.GetCenter(), 80, 2, n+i*360/8, 100, 1, false));
						Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
					}
				}
			}
			else if(!GameData::player.expired()) {
				if(GetAction() == "bIdle") {
					if(move) {
						if(bActionT.Get() > bIdleT-bOffsetT) {
							bActionT.Restart();
							move = false;
							SetAction("bAttack");
							NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
						}
						else {
							associated.box.SetPos(associated.box.GetPos()+(Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt));
							if(associated.box.GetCenter().GetDS(anchor) > 300)
								NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(anchor));
						}
					}
					else {
						if(bActionT.Get() > bIdleT-bOffsetT) {
							bActionT.Restart();
							move = true;
						}
						else {
							NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
						}
					}
				}
				else if(GetAction() == "bAttack") {
					if(bActionT.Get() > bAttackT) {
						bActionT.Restart();

						GameObject* go;
						go = new GameObject();
						go->AddComponent(new Attack(*go, "Boss", "laserbeam", associated.box.GetCenter(), 800, 0.5, GetAngleDirection(), 0, 1, true));
						Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");

						SetAction("bIdle");
						NPC::SetAngleDirection(rand()%360);
					}
				}

				int angle = associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter());
				if(angle >= 0 && angle < 90)
					SetDirection("SE");
				else if(angle >= 90 && angle < 180)
					SetDirection("SW");
				else if(angle >= 180 && angle < 270)
					SetDirection("NW");
				else if(angle >= 270 && angle < 360)
					SetDirection("NE");
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

void Boss::NotifyCollision(GameObject& other) {
	if(!transformed) {
		NPC::NotifyCollision(other);
	}
	else {
		Attack* attack = (Attack*) other.GetComponent("Attack");
		if(attack) {
			if(!attack->IsAlly("Boss")) {
				if(GetAction() != "bStun" && GetAction() != "bTransform") {
					if(bDamageT.Get() > bDamageCD) {
						Damage(attack->GetDamage());
						bDamageT.Restart();
						bActionT.Restart();
						SetAction("bHurt");
						SetSpeed(200);
						NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(other.box.GetCenter())-180);
					}
				}
				else if(GetAction() == "bStun") {
					if(attack->GetName() == "bind") {
						associated.RequestDelete();
						GameObject* go = new GameObject();
						Sprite* sp = new Sprite(*go, "assets/img/characters/boss/capture" + GetDirection() + ".png", 11, 0.1, false, 1.1);
						sp->SetScale(Vec2(2, 2));
						go->AddComponent(sp);
						go->box.SetCenter(Vec2(associated.box.x+associated.box.w/2, associated.box.y+associated.box.h-go->box.h/2));
						Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");

						GameObject* soul = new GameObject();
						soul->AddComponent(new Soul(*soul));
						soul->box.SetCenter(go->box.GetCenter());
						Game::GetInstance().GetCurrentState().AddObject(soul, "MAIN");
					}
				}
			}
		}
	}
}

bool Boss::Is(std::string type) {
	return (type == "Boss" || NPC::Is(type));
}

bool Boss::IsTransformed() {
	return transformed;
}

bool Boss::Ramble() {
	return ramble;
}
