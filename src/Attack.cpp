#include "Attack.h"
#include "Game.h"

#include "Sprite.h"
#include "Collider.h"

Attack::Attack(GameObject& associated, GameObject& owner, AttackType type, float lifeTime, 	float radius, float angle, float speed) : Component(associated) {
	Attack::owner = Game::GetInstance().GetCurrentState().GetObjectPtr(&owner, "MAIN");
	Attack::type = type;
	Attack::lifeTime = lifeTime;
	Attack::radius = radius;
	Attack::angle = angle;
	Attack::speed = speed;
	

	if(type == CENTERED) {
		associated.box.SetSize(Vec2(radius, radius)*2);
		associated.AddComponent(new Collider(associated, radius));
		Rect box = Attack::owner.lock()->box;
		associated.box.SetCenter(Vec2(box.x+box.w/2, box.y+box.h));
	}
	else if(type == DIRECTED) {
		Sprite* s = new Sprite(associated, "assets/img/sword.png");
		s->SetScale(Vec2(2, 2));
		associated.AddComponent(s);
		associated.AddComponent(new Collider(associated));
		associated.rotation = angle;
		associated.box.SetCenter(Attack::owner.lock()->box.GetCenter()+(Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*40));
	}
	else if(type == PROJECTED) {
		Sprite* s = new Sprite(associated, "assets/img/sword.png");
		s->SetScale(Vec2(2, 2));
		associated.AddComponent(s);
		associated.AddComponent(new Collider(associated));
		associated.rotation = angle;
		associated.box.SetCenter(Attack::owner.lock()->box.GetCenter()+(Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*40));
	}
}

Attack::~Attack() {

}

void Attack::Update(float dt) {
	if(owner.expired()) {
		associated.RequestDelete();
	}
	else {
		lifeTimeT.Update(dt);
		Rect box = Attack::owner.lock()->box;
		if(lifeTimeT.Get() > lifeTime)
			associated.RequestDelete();
		else if(type == CENTERED)
			associated.box.SetCenter(Vec2(box.x+box.w/2, box.y+box.h));
		else if(type == DIRECTED)
			associated.box.SetCenter(box.GetCenter()+(Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*40));
		else if(type == PROJECTED)
			associated.box.SetCenter(associated.box.GetCenter()+(Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*speed*dt));
	}
}

void Attack::NotifyCollision(GameObject& other) {
	if(other.GetComponent("Player")) {
		if(!IsAlly("Player")) {
			if(type != CENTERED) {
				associated.RequestDelete();
				associated.Deactivate();
			}
		}
	}
	else if(other.GetComponent("Monster")) {
		if(!IsAlly("Monster")) {
			if(type != CENTERED) {
				associated.RequestDelete();
				associated.Deactivate();
			}
		}
	}
	else if(other.GetComponent("MainObject")) {
		if(type != CENTERED) {
			associated.RequestDelete();
			associated.Deactivate();
		}
	}
}

bool Attack::Is(std::string type) {
	return (type == "Attack");
}

bool Attack::IsAlly(std::string ally) {
	if(!Attack::owner.expired())
		return (Attack::owner.lock()->GetComponent(ally));
	return false;
}

bool Attack::IsOwner(GameObject& owner) {
	if(!Attack::owner.expired())
		return (Attack::owner.lock() == Game::GetInstance().GetCurrentState().GetObjectPtr(&owner, "MAIN").lock());
	return false;
}
