#ifndef BOSS_H_
#define BOSS_H_

#include "NPC.h"
#include "Personality.h"
#include "Timer.h"

#include <string>

class Boss : public NPC {
private:
	bool transformed;
	bool ramble;
	Vec2 anchor;

	Timer bActionT;
	Timer bSubActionT;
	float bIdleT;
	float bWalkT;
	float bAttackT;
	float bStunT;
	float bHurtT;
	float bOffsetT;

	bool move;

	Timer bDamageT;
	float bDamageCD;

public:
	Boss(GameObject& associated, Personality p);
	~Boss();
	void Transform();
	void Damage(int damage);
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsTransformed();
	bool Ramble();
};

#endif /* BOSS_H_ */