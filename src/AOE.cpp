#include "AOE.h"
#include "Game.h"
#include "Camera.h"

#include "Collider.h"


AOE::AOE(GameObject& associated, GameObject& owner, std::string ownerName, int radius) : Component(associated) {
	AOE::owner = Game::GetInstance().GetCurrentState().GetObjectPtr(&owner, "MAIN");
	AOE::ownerName = ownerName;
	AOE::radius = radius;

	associated.AddComponent(new Collider(associated, radius));
	associated.box.SetSize(Vec2());
}

AOE::~AOE() {

}

void AOE::Update(float dt) {
	if(owner.expired())
		associated.RequestDelete();
	else
		associated.box.SetCenter(owner.lock()->box.GetCenter());
}

bool AOE::Is(std::string type) {
	return (type == "AOE");
}

int AOE::GetRadius() {
	return radius;
}

std::string AOE::GetOwnerName() {
	return ownerName;
}
