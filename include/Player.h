#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include "Timer.h"

#include <string>

class Player : public Character {
private:
	enum AttackMode { BASIC, CAPTURE };

	int pNumber;
	Timer damageT;
	float damageCD;
	AttackMode mode;

public:
	Player(GameObject& associated, std::string name, int n);
	~Player();
	void Start();
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool ModeSwitch();
	bool Attacking();
	bool Walking();
	void SetAngleDirection(float dt);
};

#endif /* PLAYER_H_ */