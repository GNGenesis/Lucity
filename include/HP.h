#ifndef HP_H_
#define HP_H_

#include "Component.h"

#include <string>
#include <vector>
#include <memory>

class HP : public Component {
private:
	std::vector<std::weak_ptr<GameObject>> health;
	int maxHealth;
	int trackHealth;

public:
	HP(GameObject& associated, int maxHealth);
	~HP();
	void Start();
	void Update(float dt);
	bool Is(std::string type);
};

#endif /* HP_H_ */