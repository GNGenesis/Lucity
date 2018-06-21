#include "Attack.h"
#include "Game.h"

#include "Sprite.h"
#include "Collider.h"

Attack::Attack(GameObject& associated, GameObject& owner, AttackType type, float lifeTime, 	float radius, float angle, float speed, int damage) : Component(associated) {
	Attack::owner = Game::GetInstance().GetCurrentState().GetObjectPtr(&owner, "MAIN");
	Attack::type = type;
	Attack::lifeTime = lifeTime;
	Attack::radius = radius;
	Attack::angle = angle;
	Attack::speed = speed;
	Attack::damage = damage;

	if(type == CENTERED) {
		associated.box.SetSize(Vec2(radius, radius)*2);
		associated.AddComponent(new Collider(associated, radius));
		Rect box = Attack::owner.lock()->box;
		associated.box.SetCenter(Vec2(box.x+box.w/2, box.y+box.h/2));
	}
	else if(type == DIRECTED) {
		std::string projectileSprite;
		if(owner.GetComponent("Player"))
			projectileSprite = "assets/img/sword.png";
		else if(owner.GetComponent("Boss"))
			projectileSprite = "assets/img/laser.png";
		Sprite* s = new Sprite(associated, projectileSprite);
		s->SetScale(Vec2(2, 2));
		associated.AddComponent(s);
		associated.AddComponent(new Collider(associated));
		associated.rotation = angle;
		associated.box.SetCenter(Attack::owner.lock()->box.GetCenter()+(Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*20));
	}
	else if(type == PROJECTED) {
		std::string projectileSprite;
		if(owner.GetComponent("Player"))
			projectileSprite = "assets/img/captureBeam.png";
		else if(owner.GetComponent("Boss"))
			projectileSprite = "assets/img/laser.png";
		Sprite* s = new Sprite(associated, projectileSprite);
		s->SetScale(Vec2(2, 2));
		associated.AddComponent(s);
		associated.AddComponent(new Collider(associated));
		associated.rotation = angle;
		associated.box.SetCenter(Attack::owner.lock()->box.GetCenter()+(Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*15));
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
			associated.box.SetCenter(Vec2(box.x+box.w/2, box.y+box.h/2));
		else if(type == DIRECTED)
			associated.box.SetCenter(box.GetCenter()+(Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*30));
		else if(type == PROJECTED)
			associated.box.SetCenter(associated.box.GetCenter()+(Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*speed*dt));
	}
}

void Attack::NotifyCollision(GameObject& other) {
	if(other.GetComponent("Player")) {
		if(!IsAlly("Player")) {
			if(type == PROJECTED) {
				associated.RequestDelete();
				associated.Deactivate();
			}
		}
	}
	else if(other.GetComponent("Monster")) {
		if(!IsAlly("Monster")) {
			if(type == PROJECTED) {
				associated.RequestDelete();
				associated.Deactivate();
			}
		}
	}
	else if(other.GetComponent("Boss")) {
		if(!IsAlly("Boss")) {
			if(type == PROJECTED) {
				associated.RequestDelete();
				associated.Deactivate();
			}
		}
	}
	else if(other.GetComponent("MainObject")) {
		if(type == PROJECTED) {
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

int Attack::GetDamage() {
	return damage;
}
