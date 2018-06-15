#ifndef ATTACK_H_
#define ATTACK_H_

#include "Component.h"
#include "Timer.h"

#include <string>
#include <memory>

class Attack : public Component {
public:
	enum AttackType { CENTERED, DIRECTED, PROJECTED };

private:
	std::weak_ptr<GameObject> owner;
	AttackType type;
	Timer lifeTimeT;
	float lifeTime;
	float radius;
	float angle;
	float speed;

public:
	Attack(GameObject& associated, GameObject& owner, AttackType type, float lifeTime, 	float radius = 0, float angle = 0, float speed = 0);
	~Attack();
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsAlly(std::string ally);
	bool IsOwner(GameObject& owner);
};

#endif /* ATTACK_H_ */