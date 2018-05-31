#ifndef EXCLAMATION_H_
#define EXCLAMATION_H_

#include "Component.h"

#include <string>
#include <memory>

class Exclamation : public Component {
private:
	std::weak_ptr<GameObject> owner;

public:
	Exclamation(GameObject& associated, GameObject& owner);
	~Exclamation();
	void Update(float dt);
	bool Is(std::string type);
};

#endif /* EXCLAMATION_H_ */