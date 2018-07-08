#ifndef FOV_H_
#define FOV_H_

#include "Component.h"

#include <string>
#include <memory>

class FOV : public Component {
private:
	std::weak_ptr<GameObject> owner;
	int radius;

public:
	FOV(GameObject& associated, GameObject& owner, int radius);
	~FOV();
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	int GetRadius();
};

#endif /* FOV_H_ */
