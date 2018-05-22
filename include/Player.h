#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"

#include <string>

class Player : public Character {
private:
	int pNumber;
	float directionAngle;

public:
	Player(GameObject& associated, int n);
	~Player();
	void Start();
	void Update(float dt);
	bool Is(std::string type);
	bool Attacking();
	bool Walking();
	void SetAngleDirection(float dt);
	float GetAngleDirection();
};

#endif /* PLAYER_H_ */