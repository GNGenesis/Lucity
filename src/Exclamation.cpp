#include "Exclamation.h"
#include "Game.h"

#include "Sprite.h"
#include "Character.h"

Exclamation::Exclamation(GameObject& associated, GameObject& owner) : Component(associated) {
	Exclamation::owner = Game::GetInstance().GetCurrentState().GetObjectPtr(&owner, "MAIN");

	associated.AddComponent(new Sprite(associated, "assets/img/exclamation.png"));
	
	if(!Exclamation::owner.expired()) {
		Character* c = (Character*) Exclamation::owner.lock()->GetComponent("Character");
		if(c) {
			associated.box.SetCenter(Exclamation::owner.lock()->box.GetCenter());
			associated.box.y = Exclamation::owner.lock()->box.y - associated.box.h;
		}
	}
}

Exclamation::~Exclamation() {

}

void Exclamation::Update(float dt) {
	if(owner.expired()) {
		associated.RequestDelete();
	}else{
		Character* character = (Character*) owner.lock()->GetComponent("Character");
		if(character) {
			associated.box.SetCenter(owner.lock()->box.GetCenter());
			associated.box.y = owner.lock()->box.y - associated.box.h;

			if(character->GetAction() != SHOCK)
				associated.RequestDelete();
		}
	}
}

bool Exclamation::Is(std::string type) {
	return (type == "Exclamation");
}