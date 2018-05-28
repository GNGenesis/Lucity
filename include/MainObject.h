#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

#include "Component.h"

#include <string>
#include <vector>
#include <memory>

class MainObject : public Component {
private:
	std::string objectName;
	int hp;
	Vec2 scale;
	bool miscObject;
	bool destructible;

public:
	MainObject(GameObject& associated, std::string objectName, int hp, Vec2 scale = {0, 0}, bool miscObject = false, bool destructible = false);
	~MainObject();
	void Start();
	void Damage(int damage);
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
};

#endif /* MAINOBJECT_H_ */
