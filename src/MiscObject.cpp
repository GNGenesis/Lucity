#include "MiscObject.h"
#include "Game.h"

#include "Sprite.h"


MiscObject::MiscObject(GameObject& associated, GameObject& mainObject, std::string miscName, Vec2 scale) : Component(associated) {
	MiscObject::mainObject = Game::GetInstance().GetCurrentState().GetObjectPtr(&mainObject, "MAIN");

	std::string path = "assets/img/objects/" + miscName + "_top.png";
	Sprite* object = new Sprite(associated, path);
	object->SetScale(scale);
	associated.AddComponent(object);
}

MiscObject::~MiscObject() {

}

void MiscObject::Update(float dt) {
	if(mainObject.expired()) {
		associated.RequestDelete();
	}
	else {
		associated.box.x = mainObject.lock()->box.GetCenter().x - associated.box.w/2;
		associated.box.y = mainObject.lock()->box.y - associated.box.h;
	}
}

bool MiscObject::Is(std::string type) {
	return (type == "MiscObject");
}
