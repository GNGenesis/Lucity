#include "Game.h"
#include "MainObject.h"
#include "MiscObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "AOE.h"
#include "Character.h"
#include "Player.h"


MainObject::MainObject(GameObject& associated, std::string objectName,float scaleX,float scaleY, int nMiscObjects, bool isDestructable) : Component(associated) {
	
	MainObject::objectName = objectName;
	MainObject::scaleX = scaleX;
	MainObject::scaleY = scaleY;
	MainObject::nMiscObjects = nMiscObjects;
	MainObject::IsDestructable = IsDestructable;

	std::string path = "assets/img/Objects/" + objectName + ".png";
	this->hp = 1;
	Sprite *object = new Sprite(associated, path);
	object->SetScale(Vec2(scaleX, scaleY));
	associated.AddComponent(object);
	associated.AddComponent(new Collider(associated, Vec2(1, 0), Vec2(0, -associated.box.h / 2)));
	associated.AddComponent(new AOE(associated,2.0f));
}

MainObject::~MainObject() {

}

void MainObject::Start() {
	for(int i = 0; i < nMiscObjects; i++){
		GameObject* go = new GameObject();
		if (MainObject::objectName == "tree") {
			go->AddComponent(new MiscObject(*go,associated,"tree_top",Vec2(this->scaleX,this->scaleY)));
		}
		MiscArray.push_back(Game::GetInstance().GetCurrentState().AddObject(go,"MISC"));
	}
}

void MainObject::Update(float dt) {
	if (hp == 0) {
		//Rolar destruição do Objeto
	}
}

void MainObject::Render() {

}
void MainObject::NotifyCollision(GameObject & other){

	Character* monster = (Character*)other.GetComponent("Monster");
	if (monster) {
		if (monster->GetAction() == ATTACK) {
			if (IsDestructable) {
				this->hp = 0;
			}
		}
	}
	Character* character = (Character*)other.GetComponent("Character");
	if (character) {
		Collider* c = (Collider*)associated.GetComponent("Collider");
		if (c) {
			if (character->GetAngleDirection() >= 0 && character->GetAngleDirection() < 180)
				other.box.y = c->box.y - other.box.h - 1;
			else if (character->GetAngleDirection() >= 180 && (character->GetAngleDirection() < 360))
				other.box.y = c->box.y + c->box.h + 1;
		}
	}
}

bool MainObject::Is(std::string type) {
	return (type == "MainObject");
}

std::string MainObject::GetObjectName() {
	return objectName;
}
