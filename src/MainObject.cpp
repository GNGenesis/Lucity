#include "MainObject.h"
#include "Game.h"
#include "Collision.h"

#include "Sprite.h"
#include "Collider.h"
#include "MiscObject.h"
#include "Attack.h"

MainObject::MainObject(GameObject& associated, std::string objectName, int hp, Vec2 scale, bool miscObject, bool destructible) : Component(associated) {
	MainObject::objectName = objectName;
	MainObject::hp = hp;	
	MainObject::scale = scale;
	MainObject::miscObject = miscObject;
	MainObject::destructible = destructible;

	std::string path;
	if(miscObject)
		path = "assets/img/objects/" + objectName + "_bottom.png";
	else
		path = "assets/img/objects/" + objectName + "_full.png";

	Sprite* object;
	if(objectName == "fountain")
		object = new Sprite(associated, path, 7, 0.1);
	else
		object = new Sprite(associated, path);
	object->SetScale(scale);
	associated.AddComponent(object);
	associated.AddComponent(new Collider(associated));
}

MainObject::~MainObject() {

}

void MainObject::Start() {
	if(miscObject) {
		GameObject* go = new GameObject();
		go->AddComponent(new MiscObject(*go, associated, objectName, scale));
		Game::GetInstance().GetCurrentState().AddObject(go, "MISC");
	}
}

void MainObject::Damage(int damage) {
	if(destructible) {
		hp -= damage;
	}

	if(hp < 1) {
		associated.RequestDelete();
		GameObject* go = new GameObject();
		Sprite* sp;
		if(objectName == "fountain")
			sp = new Sprite(*go, "assets/img/objects/" + objectName + "_end.png", 6, 0.1);
		else
			sp = new Sprite(*go, "assets/img/objects/" + objectName + "_end.png");
		sp->SetScale(scale);
		go->AddComponent(sp);
		go->box.SetPos(associated.box.GetPos()+Vec2(associated.box.w/2, associated.box.h)-Vec2(go->box.w/2, go->box.h));
		Game::GetInstance().GetCurrentState().AddObject(go, "EFFECT");
	}
}

void MainObject::Update(float dt) {

}

void MainObject::NotifyCollision(GameObject & other){
	Attack* attack = (Attack*) other.GetComponent("Attack");
	if(attack)
		if(attack->IsAlly("Monster"))
			Damage(attack->GetDamage());

	if(other.GetComponent("Character") || other.GetComponent("Soul")) {
		Collider* collider = (Collider*) associated.GetComponent("Collider");
		if(collider) {
			Rect box = associated.box;
			box.SetSize(box.w, 0);
			Collision::SolidCollision(other.box, box);
		}
	}
}

bool MainObject::Is(std::string type) {
	return (type == "MainObject");
}

std::string MainObject::GetName() {
	return objectName;
}
