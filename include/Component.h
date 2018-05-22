#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "GameObject.h"

#include <string>

class Component {
protected:
	GameObject& associated;
	bool active;

public:
	Component(GameObject& associated);
	virtual ~Component();
	virtual	void Start();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void NotifyCollision(GameObject& other);
	virtual void Activate();
	virtual void Deactivate();
	virtual bool IsActive();
	virtual bool Is(std::string type) = 0;
};

#endif /* COMPONENT_H_ */
