#include "FOV.h"
#include "Game.h"
#include "Camera.h"

#include "Collider.h"


FOV::FOV(GameObject& associated, GameObject& owner, int radius) : Component(associated) {
	FOV::owner = Game::GetInstance().GetCurrentState().GetObjectPtr(&owner, "MAIN");
	FOV::radius = radius;

	associated.AddComponent(new Collider(associated, radius));
	associated.box.SetSize(Vec2());
}

FOV::~FOV() {

}

void FOV::Update(float dt) {
	if(owner.expired())
		associated.RequestDelete();
	else
		associated.box.SetCenter(owner.lock()->box.GetCenter());
}

void FOV::NotifyCollision(GameObject& other) {
	if(other.GetComponent("NPC") || other.GetComponent("MainObject"))
		if(!owner.expired())
			owner.lock()->NotifyCollision(other);
}

bool FOV::Is(std::string type) {
	return (type == "FOV");
}

int FOV::GetRadius() {
	return radius;
}
