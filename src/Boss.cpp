#include "Boss.h"
#include "Game.h"
#include "GameData.h"
#include "Camera.h"

#include "Sprite.h"
#include "Attack.h"

#include <math.h>

Boss::Boss(GameObject& associated, Personality p) : NPC(associated, p) {
	SetHealth(1);
	transformed = false;
	ramble = false;
	bIdleT = 2;
	bAttackT = 0.5;
	bStunT = 2;
	bHurtT = 2;
	bDamageCD = 2;
}

Boss::~Boss() {

}

void Boss::Transform() {
	transformed = true;
	SetHealth(6);
	SetSpeed(50);
	SetAction("bTransform");
	SetDirection("");
	anchor = associated.box.GetCenter();
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
					bOffsetT = (30-GameData::nCivilians)/30;
					SetAction("bIdle");
					SetDirection("SE");
				}
			}
			else if(GetAction() == "bStun") {
				if(bActionT.Get() > bStunT-bOffsetT) {
					bActionT.Restart();
					SetAction("bAttack");
					SetDirection("SE");
					SetHealth(1);
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
					if(bActionT.Get() > bIdleT-bOffsetT) {
						bActionT.Restart();
						SetAction("bAttack");
					}
					else {
						associated.box.SetPos(associated.box.GetPos()+(Vec2(Vec2::Cos(GetAngleDirection()), Vec2::Sin(GetAngleDirection()))*GetSpeed()*dt));
						if(associated.box.GetCenter().GetDS(anchor) > 200)
							NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(anchor));
					}
				}
				else if(GetAction() == "bAttack") {
					NPC::SetAngleDirection(associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter()));
					if(bActionT.Get() > bAttackT) {
						bActionT.Restart();

						GameObject* go;
						go = new GameObject();
						go->AddComponent(new Attack(*go, "Boss", "laserbeam", associated.box.GetCenter(), 250, 0.5, GetAngleDirection(), 0, 1, true));
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
						go->AddComponent(new Sprite(*go, "assets/img/characters/boss/capture.png", 7, 0.12, false, 0.84));
						go->box.SetCenter(Vec2(associated.box.x+associated.box.w/2, associated.box.y+associated.box.h-go->box.h/2));
						Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
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
