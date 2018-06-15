#ifndef BOSS_H_
#define BOSS_H_

#include "NPC.h"
#include "Personality.h"
#include "Vec2.h"
#include "Timer.h"

#include <string>

class Boss : public NPC {
private:
	bool rawr;
	bool attacked;
	Timer mActionT;
	float mIdleT;
	float mWalkT;
	float mAttackT;
	float mOffsetT;
	Timer mDamageT;
	float mDamageCD;

public:
	Boss(GameObject& associated, Personality p);
	~Boss();
	void Damage(int damage);
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	Vec2 initPos;
};

#endif /* BOSS_H_ */
