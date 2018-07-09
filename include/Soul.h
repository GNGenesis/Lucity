#ifndef SOUL_H_
#define SOUL_H_

#include "Component.h"
#include "Timer.h"

#include <string>

class Soul : public Component {
private:
	Timer startT;
	bool started;

public:
	Soul(GameObject& associated);
	~Soul();
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
};

#endif /* SOUL_H_ */