#ifndef CHARACTER_H_
#define CHARACTER_H_

#define IDLE "idle"
#define WALK "walk"
#define SHOCK "shock"
#define PANIC "panic"
#define ATTACK "attack"

#include "Component.h"

#include <string>

class Character : public Component {
private:
	int hp;
	int speed;
	std::string action;
	std::string direction;

public:
	Character(GameObject& associated);
	~Character();
	void SetHealth(int hp);
	void SetSpeed(int speed);
	void SetAction(std::string action);
	void SetDirection(std::string direction);
	virtual void Damage(int damage);
	virtual void Update(float dt) = 0;
	virtual void Render();
	virtual bool Is(std::string type) = 0;
	int GetHealth();
	int GetSpeed();
	std::string GetAction();
	std::string GetDirection();
	std::string GetSprite();
};

#endif /* CHARACTER_H_ */