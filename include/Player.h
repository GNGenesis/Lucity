#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "Timer.h"

#include <string>

class Player : public Character {
private:
	int pNumber;
	Vec2 mousePos;

	Timer damageT;
	float damageCD;

public:
	Player(GameObject& associated, std::string name, int n);
	~Player();
	void Start();
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsWalking();
	bool IsWalkingBackwards();
	void SetAngleDirection(float dt);
};

#endif /* PLAYER_H_ */