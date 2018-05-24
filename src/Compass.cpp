#include "Compass.h"
#include "Game.h"

#include "Sprite.h"
#include "Player.h"

Compass::Compass(GameObject& associated, GameObject& player, std::string pNumber) : Component(associated) {
	Compass::player = Game::GetInstance().GetCurrentState().GetObjectPtr(&player, "MAIN");
	arc = 0;
	associated.AddComponent(new Sprite(associated, "assets/img/compassP"+pNumber+".png"));
}

Compass::~Compass() {

}

void Compass::Update(float dt) {
	if(player.expired()) {
		associated.RequestDelete();
	}else{
		Player* p = (Player*) player.lock()->GetComponent("Player");
		if(p) {
			arc = p->GetAngleDirection();
			associated.rotation = arc-90;
			associated.box.SetCenter(player.lock()->box.GetCenter()+(Vec2(Vec2::Cos(arc), Vec2::Sin(arc))*30));
		}
	}
}

bool Compass::Is(std::string type) {
	return (type == "Compass");
}
