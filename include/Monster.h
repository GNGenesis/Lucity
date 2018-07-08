#ifndef MONSTER_H_
#define MONSTER_H_

#include "NPC.h"
#include "Personality.h"
#include "Timer.h"

#include <string>

class Monster : public NPC {
private:
	bool transformed;

	Timer mActionT;
	float mIdleT;
	float mWalkT;
	float mAttackT;
	float mStunT;
	float mOffsetT;

	Timer mDamageT;
	float mDamageCD;

public:
	Monster(GameObject& associated, Personality p);
	~Monster();
	void Transform();
	void Damage(int damage);
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsTransformed();
};

#endif /* MONSTER_H_ */