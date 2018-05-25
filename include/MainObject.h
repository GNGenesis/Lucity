#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

#include "Component.h"
#include "Timer.h"

#include <string>
#include <vector>
#include <memory>

class MainObject : public Component {
private:
	
	int hp;
	int  nMiscObjects;
	bool IsDestructable;
	float scaleX, scaleY;
	std::string objectName;
	std::vector<std::weak_ptr<GameObject>> MiscArray;


public:
	static int alienCount;

	MainObject(GameObject& associated, std::string objectName,float scaleX = 1,float scaleY = 1, int nMiscObjects = 0,bool IsDestructable = false);
	~MainObject();
	void Start();
	void Damage(int damage);
	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
};

#endif
