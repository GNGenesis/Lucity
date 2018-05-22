#include "Monster.h"

Monster::Monster(GameObject& associated, Personality p) : NPC(associated, p) {
	SetHealth(28);
	rawr = false;
}

Monster::~Monster() {

}

void Monster::Update(float dt) {
	if(!rawr)
		NPC::Update(dt);
}

void Monster::NotifyCollision(GameObject& other) {
	if(!rawr)
		NPC::NotifyCollision(other);
}

bool Monster::Is(std::string type) {
	return (type == "Monster" || Character::Is(type));
}
