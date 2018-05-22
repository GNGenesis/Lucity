#ifndef NPC_H_
#define NPC_H_

#include "Character.h"
#include "Personality.h"
#include "Timer.h"

#include <string>
#include <vector>

class NPC : public Character {
private:
	Personality person;
	Timer actionT;
	float offsetT;
	Timer damageT;
	float damageCD;
	float directionAngle;

public:
	NPC(GameObject& associated, Personality p);
	~NPC();
	void Start();
	void Damage(int damage);
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	void SetAngleDirection(int angle);
	float GetAngleDirection();
};

#endif /* NPC_H_ */