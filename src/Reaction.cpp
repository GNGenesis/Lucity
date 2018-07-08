#include "Reaction.h"
#include "Game.h"

#include "Sprite.h"
#include "Character.h"

Reaction::Reaction(GameObject& associated, GameObject& owner, std::string reaction) : Component(associated) {
	Reaction::owner = Game::GetInstance().GetCurrentState().GetObjectPtr(&owner, "MAIN");

	associated.AddComponent(new Sprite(associated, "assets/img/" + reaction + ".png"));
	
	if(!Reaction::owner.expired()) {
		Character* c = (Character*) Reaction::owner.lock()->GetComponent("Character");
		if(c) {
			associated.box.SetCenter(Reaction::owner.lock()->box.GetCenter());
			associated.box.y = Reaction::owner.lock()->box.y - associated.box.h;
		}
	}
}

Reaction::~Reaction() {

}

void Reaction::Update(float dt) {
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

bool Reaction::Is(std::string type) {
	return (type == "Reaction");
}