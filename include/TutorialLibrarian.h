#ifndef TUTORIALLIBRARIAN_H_
#define TUTORIALLIBRARIAN_H_

#include "Monster.h"
#include "Personality.h"
#include "Timer.h"

#include <string>

class TutorialLibrarian : public Monster {
private:/*
	bool transformed;

	Timer mActionT;
	float mIdleT;
	float mWalkT;
	float mAttackT;
	float mStunT;
	float mOffsetT;

	Timer mDamageT;
	float mDamageCD;*/

public:
	TutorialLibrarian(GameObject& associated, Personality p);
	~TutorialLibrarian();
	void Update(float dt);/*
	void Transform();
	void Damage(int damage);
	void NotifyCollision(GameObject& other);
	bool IsTransformed();*/
	bool Is(std::string type);
};

#endif /* TUTORIALLIBRARIAN_H_ */
