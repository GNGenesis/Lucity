#include "Monster.h"
#include "GameData.h"

Monster::Monster(GameObject& associated, Personality p) : NPC(associated, p) {
	SetHealth(3);
	rawr = false;

	GameData::nMonsters++;
	GameData::nCivilians--;
}

Monster::~Monster() {
	GameData::nMonsters--;
	GameData::nCivilians++;
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
