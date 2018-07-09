#ifndef NPCTUTORIAL_H_
#define NPCTUTORIAL_H_

#include "Character.h"
#include "Personality.h"
#include "Timer.h"
#include "Vec2.h"

#include <string>

class NPCTutorial : public Character {
protected:
	Personality person;

	Timer actionT;
	float offsetT;

	Timer damageT;
	float damageCD;

	bool scared;
	bool underTutorialControl;

	Vec2 initPos;
	Vec2 destination;

public:
	NPCTutorial(GameObject& associated, Personality p);
	~NPCTutorial();
	virtual void Start();
	virtual void Damage(int damage);
	virtual void Update(float dt);
	void WalkToPoint(Vec2 destination, float dt);
	virtual void NotifyCollision(GameObject& other);
	virtual bool Is(std::string type);
	void SetAngleDirection(int angle);
	void SetPerson(Personality p);
	std::string GetName();
	void ToggleTutorialControl();
	bool GetTutorialControl();
};

#endif /* NPCTUTORIAL_H_ */
