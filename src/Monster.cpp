#include "Monster.h"
#include "GameData.h"

Monster::Monster(GameObject& associated, Personality p) : NPC(associated, p) {
	SetHealth(2);
	rawr = false;

	GameData::nMonsters++;
	GameData::nCivilians--;
}

Monster::~Monster() {
	GameData::nMonsters--;
	GameData::nCivilians++;
}

void Monster::Damage(int damage) {
	SetHealth(GetHealth()-damage);
	//rawr = true;
	if(GetHealth() < 1)
		associated.RequestDelete();
}

void Monster::Update(float dt) {
	if(!rawr) {
		NPC::Update(dt);
	}
	else {
		SetAction("mIdle");
	}
}

void Monster::NotifyCollision(GameObject& other) {
	if(!rawr)
		NPC::NotifyCollision(other);
}

bool Monster::Is(std::string type) {
	return (type == "Monster" || NPC::Is(type));
}
