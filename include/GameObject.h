#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"

#include <string>
#include <vector>
#include <memory>

class Component;

class GameObject {
private:
	std::vector<std::shared_ptr<Component>> components;
	bool started;
	bool active;
	bool isDead;

public:
	Rect box;
	float rotation;

	GameObject();
	~GameObject();
	void Start();
	//std::shared_ptr<Component> AddComponent(Component* cpt);
	//std::shared_ptr<Component> AddComponentAsFirst(Component* cpt);
	Component* AddComponent(Component* cpt);
	Component* AddComponentAsFirst(Component* cpt);
	Component* GetComponent(std::string type);
	void RemoveComponent(Component* cpt);
	void RequestDelete();
	void Update(float dt) ;
	void Render();
	void NotifyCollision(GameObject& other);
	void Activate();
	void Deactivate();
	bool IsActive();
	bool IsDead();
};

#endif /* GAMEOBJECT_H_ */
