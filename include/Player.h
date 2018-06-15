#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "Timer.h"

#include <string>

class Player : public Character {
private:
	int pNumber;
	Timer damageT;
	float damageCD;

public:
	Player(GameObject& associated, std::string name, int n);
	~Player();
	void Start();
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool Attacking();
	bool Walking();
	void SetAngleDirection(float dt);
};

#endif /* PLAYER_H_ */