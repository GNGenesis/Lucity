#ifndef REACTION_H_
#define REACTION_H_

#include "Component.h"

#include <string>
#include <memory>

class Reaction : public Component {
private:
	std::weak_ptr<GameObject> owner;

public:
	Reaction(GameObject& associated, GameObject& owner, std::string reaction);
	~Reaction();
	void Update(float dt);
	bool Is(std::string type);
};

#endif /* REACTION_H_ */