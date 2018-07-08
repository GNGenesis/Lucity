#ifndef MONSTERTUTORIAL_H_
#define MONSTERTUTORIAL_H_

#include "NPCTutorial.h"
#include "Personality.h"
#include "Timer.h"

#include <string>

class MonsterTutorial : public NPCTutorial {
protected:
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
	MonsterTutorial(GameObject& associated, Personality p);
	~MonsterTutorial();
	void Transform();
	void Damage(int damage);
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsTransformed();
};

#endif /* MONSTERTUTORIAL_H_ */
