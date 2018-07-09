#include "Attack.h"
#include "Game.h"
#include "GameData.h"

#include "Collider.h"

Attack::Attack(GameObject& associated, std::string owner, std::string name, Vec2 origin, float offset, float lifeTime, float direction, float speed,
			   int damage, bool pierce) : Component(associated) {
	Attack::owner = owner;
	Attack::name = name;
	Attack::lifeTime = lifeTime;
	Attack::direction = direction;
	Attack::speed = speed;
	Attack::damage = damage;
	Attack::pierce = pierce;
	
	Sprite* sp;
	int scale;
	int frameCount;
	if(name == "blast") {
		scale = 2;
		frameCount = 1;
	}
	else if(name == "bubbles") {
		scale = 2;
		frameCount = 3;
	}
	else if(name == "bind") {
		scale = 2;
		frameCount = 3;
	}
	else if(name == "energyball") {
		scale = 2;
		frameCount = 3;
	}
	else if(name == "laserbeam") {
		scale = 2;
		frameCount = 4;
	}
	else {
		scale = 2;
		frameCount = 2;
	}
	sp = new Sprite(associated, "assets/img/effects/" + name + ".png", frameCount, 0.1);
	sp->SetScale(Vec2(scale, scale));
	associated.AddComponent(sp);
	associated.AddComponent(new Collider(associated));
	associated.rotation = direction;
	associated.box.SetCenter(origin+(Vec2(Vec2::Cos(direction), Vec2::Sin(direction))*offset));
}

Attack::~Attack() {

}

void Attack::OnDeath() {
	GameObject* go = new GameObject();

	if(name == "bind") {
		Sprite* sp = new Sprite(*go, "assets/img/effects/" + name + "_end.png", 3, 0.1, false, 0.3);
		sp->SetScale(Vec2(2, 2));
		go->AddComponent(sp);
		go->rotation = direction;
		go->box.SetCenter(associated.box.GetCenter());
		Game::GetInstance().GetCurrentState().AddObject(go, "EFFECT");
	}
	else if(name == "bubbles") {
		go->AddComponent(new Sprite(*go, "assets/img/effects/" + name + "_end.png", 3, 0.1, false, 0.3));
		go->box.SetCenter(associated.box.GetCenter());
		Game::GetInstance().GetCurrentState().AddObject(go, "EFFECT");
	}
	else if(name == "fireball") {
		go->AddComponent(new Attack(*go, "Player", "blast", Vec2(), 0.3, 0, 0, 1, true));
		go->box.SetCenter(associated.box.GetCenter());
		Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
	}
	else {
		//do nothing
	}
}

void Attack::Update(float dt) {
	if(!GameData::paused) {
		lifeTimeT.Update(dt);
		if(lifeTimeT.Get() > lifeTime) {
			associated.RequestDelete();
			OnDeath();
		}
		else {
			associated.box.SetCenter(associated.box.GetCenter()+(Vec2(Vec2::Cos(direction), Vec2::Sin(direction))*speed*dt));
		}
	}
}

void Attack::NotifyCollision(GameObject& other) {
	if(!pierce) {
		if(other.GetComponent("Player")) {
			if(!IsAlly("Player")) {
				associated.RequestDelete();
				associated.Deactivate();
				OnDeath();
			}
		}
		else if(other.GetComponent("NPC")) {
			if(other.GetComponent("Monster")) {
				if(!IsAlly("Monster")) {
					associated.RequestDelete();
					associated.Deactivate();
					OnDeath();
				}
			}
			else if(other.GetComponent("Boss")) {
				if(!IsAlly("Boss")) {
					associated.RequestDelete();
					associated.Deactivate();
					OnDeath();
				}
			}
			else {
				associated.RequestDelete();
				associated.Deactivate();
				OnDeath();
			}
		}
		else if(other.GetComponent("Attack")) {
			Attack* a = (Attack*) other.GetComponent("Attack");
			if(!IsAlly(a->GetOwner())) {
				associated.RequestDelete();
				associated.Deactivate();
				OnDeath();
			}
		}
		else if(other.GetComponent("MainObject")) {
			associated.RequestDelete();
			associated.Deactivate();
			OnDeath();
		}
	}
}

bool Attack::Is(std::string type) {
	return (type == "Attack");
}

bool Attack::IsAlly(std::string ally) {
	return (ally == owner);
}

int Attack::GetDamage() {
	return damage;
}

std::string Attack::GetOwner() {
	return owner;
}

std::string Attack::GetName() {
	return name;
}
