#include "HP.h"
#include "Game.h"

#include "Sprite.h"
#include "Character.h"

#include <math.h>

HP::HP(GameObject& associated, int maxHealth) : Component(associated) {
	HP::maxHealth = maxHealth;
	HP::trackHealth = maxHealth;
}

HP::~HP() {
	for(int i = maxHealth-1; i >= 0; i--)
		health[i].lock()->RequestDelete();	
	health.clear();
}

void HP::Start() {
	for(int i = 0; i < maxHealth; i++) {
		GameObject* go = new GameObject();
		Sprite* sp = new Sprite(*go, "assets/img/HUD/health.png", 5, 0, false);
		sp->SetScale(Vec2(2, 2));
		go->AddComponent(sp);
		health.emplace_back(Game::GetInstance().GetCurrentState().AddObject(go, "GUI"));
	}
}

void HP::Update(float dt) {
	for(int i = 0; i < maxHealth; i++) {
		if(!health[i].expired()) {
			if(maxHealth%2 != 1)
				health[i].lock()->box.SetPos((associated.box.x+associated.box.w/2)+(i-maxHealth/2)*11, associated.box.y-health[i].lock()->box.h/2-10);
			else
				health[i].lock()->box.SetCenter((associated.box.x+associated.box.w/2)+(i-maxHealth/2)*11, associated.box.y-10);
		}
	}

	Character* c = (Character*) associated.GetComponent("Character");
	if(c) {
		if(c->GetHealth() < trackHealth && c->GetHealth() >= 0) {
			for(int i = trackHealth-1; i < maxHealth; i++) {
				Sprite* s = (Sprite*) health[i].lock()->GetComponent("Sprite");
				s->SetFrameTime(0.2);
			}
		}
		else if(c->GetHealth() > trackHealth && c->GetHealth() <= maxHealth) {
			for(int i = trackHealth; i < c->GetHealth(); i++) {
				Sprite* s = (Sprite*) health[i].lock()->GetComponent("Sprite");
				s->SetFrame(0);
				s->SetFrameTime(0);
			}
		}
		trackHealth = c->GetHealth();
	}
}

bool HP::Is(std::string type) {
	return (type == "HP");
}
