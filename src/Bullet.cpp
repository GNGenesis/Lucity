#include "Bullet.h"
#include "Game.h"

#include "Sprite.h"
#include "Collider.h"

Bullet::Bullet(GameObject& associated, Sprite* sprite, std::string owner, 
			   float maxDistance, float angle, float speed, int damage) : Component(associated) {
	Bullet::owner = owner;
	Bullet::speed = Vec2(speed*Vec2::Cos(angle), speed*Vec2::Sin(angle));
	Bullet::damage = damage;
	distanceLeft = maxDistance;
	associated.rotation = angle;

	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
}

Bullet::~Bullet() {

}

void Bullet::Update(float dt) {
	if(distanceLeft > 0) {
		associated.box.x += speed.x*dt;
		associated.box.y += speed.y*dt;
		distanceLeft -= Vec2().GetDS(Vec2(speed.x*dt, speed.y*dt));
	}else{
		associated.RequestDelete();
	}
}

void Bullet::Render() {

}

void Bullet::NotifyCollision(GameObject& other) {
	if(!other.GetComponent("Bullet")) {
		if(!other.GetComponent(owner)) {
			associated.RequestDelete();
			GameObject* go = new GameObject();
			Sprite* sprite = new Sprite(*go, "assets/img/penguindeath.png", 5, 0.15, false, 0.75);
			go->AddComponent(sprite);
			sprite->SetScale(Vec2(0.25, 0.25));
			go->box.SetCenter(associated.box.GetCenter());
			go->rotation = rand()%360;
			Game::GetInstance().GetCurrentState().AddObject(go);
		}
	}
}

bool Bullet::Is(std::string type) {
	return (type == "Bullet");
}

bool Bullet::IsOwner(std::string owner) {
	return (Bullet::owner == owner);
}

int Bullet::GetDamage() {
	return damage;
}
