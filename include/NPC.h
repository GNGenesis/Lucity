#ifndef NPC_H_
#define NPC_H_

#include "Character.h"
#include "Personality.h"
#include "Timer.h"

#include <string>

class NPC : public Character {
private:
	Personality person;
	Timer actionT;
	float offsetT;
	Timer damageT;
	float damageCD;
	bool scared;

public:
	NPC(GameObject& associated, Personality p);
	~NPC();
	virtual void Update(float dt);
	virtual void NotifyCollision(GameObject& other);
	virtual bool Is(std::string type);
	void SetAngleDirection(int angle);
};

#endif /* NPC_H_ */