#ifndef ATTACK_H_
#define ATTACK_H_

#include "Component.h"
#include "Sprite.h"
#include "Timer.h"

#include <string>
#include <memory>

class Attack : public Component {
private:
	std::string owner;
	std::string name;
	Timer lifeTimeT;
	float lifeTime;
	float direction;
	float speed;
	int damage;
	bool pierce;

public:
	Attack(GameObject& associated, std::string owner, std::string name, Vec2 origin, float offset, float lifeTime, float direction = 0, float speed = 0,
		   int damage = 1, bool pierce = false);
	~Attack();
	void OnDeath();
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsAlly(std::string ally);
	int GetDamage();
	std::string GetOwner();
	std::string GetName();
};

#endif /* ATTACK_H_ */