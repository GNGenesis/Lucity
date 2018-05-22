#ifndef BULLET_H_
#define BULLET_H_

#include "Component.h"

#include <string>

class Sprite;

class Bullet : public Component {
private:
	std::string owner;
	Vec2 speed;
	int damage;
	float distanceLeft;

public:
	Bullet(GameObject& associated, Sprite* sprite, std::string owner, 
		   float maxDistance, float angle, float speed, int damage);
	~Bullet();
	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsOwner(std::string owner);
	int GetDamage();

};

#endif /* BULLET_H_ */
