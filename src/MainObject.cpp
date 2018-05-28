#include "MainObject.h"
#include "Game.h"
#include "Collision.h"

#include "Sprite.h"
#include "Collider.h"
#include "MiscObject.h"
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
	if(hp < 0)
		associated.RequestDelete();
}

void MainObject::Update(float dt) {
	
}

void MainObject::NotifyCollision(GameObject & other){
	Character* character = (Character*) other.GetComponent("Character");
	if(character) {
		if(other.GetComponent("Character")) {
			if(character->GetAction() == ATTACK) {
				Damage(1);
			}
		}

		Collider* collider = (Collider*) associated.GetComponent("Collider");
		if(collider) {
			Rect box = associated.box;
			//box.SetPos(box.x+1, box.y);
			//box.SetSize(box.w-2, 0);
			box.SetSize(box.w, 0);
			Collision::SolidCollision(other.box, box);
		}
	}
}

bool MainObject::Is(std::string type) {
	return (type == "MainObject");
}
