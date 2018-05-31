#ifndef AOE_H_
#define AOE_H_

#include "Component.h"

#include <string>
#include <memory>

class AOE : public Component {
private:
	std::weak_ptr<GameObject> owner;
	std::string ownerName;
	int radius;

public:
	AOE(GameObject& associated, GameObject& owner, std::string ownerName, int radius);
	~AOE();
	void Update(float dt);
	bool Is(std::string type);
	int GetRadius();
	std::string GetOwnerName();
};

#endif /* AOE_H_ */
