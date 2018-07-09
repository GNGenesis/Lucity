#include "Soul.h"
#include "Game.h"
#include "GameData.h"

#include "Sprite.h"
#include "Collider.h"

Soul::Soul(GameObject& associated) : Component(associated) {
	Sprite* sp = new Sprite(associated, "assets/img/effects/soul.png", 4, 0.1);
	sp->SetScale(Vec2(2, 2));
	associated.AddComponent(sp);
	associated.AddComponent(new Collider(associated));
	associated.GetComponent("Sprite")->Deactivate();
	started = false;
}

Soul::~Soul() {

}

void Soul::Update(float dt) {
	if(!started) {	
		startT.Update(dt);
		if(startT.Get() > 1.1) {
			associated.GetComponent("Sprite")->Activate();
			started = true;
		}
	}
	else {
		if(!GameData::paused) {
			if(!GameData::player.expired()) {
				int angle = associated.box.GetCenter().GetAngle(GameData::player.lock()->box.GetCenter());
				associated.box.SetCenter(associated.box.GetCenter()+Vec2(Vec2::Cos(angle), Vec2::Sin(angle))*100*dt);
			}
		}
	}
}

void Soul::NotifyCollision(GameObject& other) {
	if(other.GetComponent("Player")) {
		associated.RequestDelete();
		GameObject* go = new GameObject();
		Sprite* sp = new Sprite(*go, "assets/img/effects/soul_end.png", 4, 0.1, false, 0.4);
		sp->SetScale(Vec2(2, 2));
		go->AddComponent(sp);
		go->box.SetCenter(associated.box.GetCenter());
		Game::GetInstance().GetCurrentState().AddObject(go, "MAIN");
	}
}

bool Soul::Is(std::string type) {
	return (type == "Soul");
}
