#ifndef COMPASS_H_
#define COMPASS_H_

#include "Component.h"

#include <string>
#include <memory>

class Compass : public Component {
private:
	std::weak_ptr<GameObject> player;
	float arc;

public:
	Compass(GameObject& associated, GameObject& player, std::string pNumber);
	~Compass();
	void Update(float dt);
	bool Is(std::string type);
};

#endif /* COMPASS_H_ */