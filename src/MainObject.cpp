#include "MainObject.h"
#include "Game.h"
#include "Collision.h"

#include "Sprite.h"
#include "Collider.h"
#include "MiscObject.h"
#include "Attack.h"
#include "Character.h"


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
	Sprite* object = new Sprite(associated, path);
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
	if(destructible)
		hp -= damage;
	if(hp < 1)
		associated.RequestDelete();
}

void MainObject::Update(float dt) {

}

void MainObject::NotifyCollision(GameObject & other){
	Attack* attack = (Attack*) other.GetComponent("Attack");
	if(attack)
		if(attack->IsAlly("Monster"))
			Damage(attack->GetDamage());

	Character* character = (Character*) other.GetComponent("Character");
	if(character) {
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
