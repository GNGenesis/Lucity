#include "Game.h"
#include "MiscObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "Character.h"


MiscObject::MiscObject(GameObject& associated, GameObject& mainObject,std::string miscNome, Vec2 scale) : Component(associated){
	MiscObject::mainObject = Game::GetInstance().GetCurrentState().GetObjectPtr(&mainObject,"MAIN");
	std::string path = "assets/img/Objects/" + miscNome + ".png";
	Sprite *object = new Sprite(associated, path);
	object->SetScale(scale);
	associated.AddComponent(object);
}

MiscObject::~MiscObject() {

}

void MiscObject::Update(float dt) {
	if (mainObject.expired()) {
		associated.RequestDelete();
	}
	else {
		associated.box.x = mainObject.lock()->box.GetCenter().x - associated.box.w/2;
		associated.box.y = mainObject.lock()->box.y - associated.box.h;
	}
}

void MiscObject::Render() {

}

bool MiscObject::Is(std::string type) {
	return (type == "MiscObject");
}
