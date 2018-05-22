#ifndef MONSTER_H_
#define MONSTER_H_

#include "NPC.h"
#include "Personality.h"
#include "Timer.h"

#include <string>

class Monster : public NPC {
private:
	bool rawr;

public:
	Monster(GameObject& associated, Personality p);
	~Monster();
	void Update(float dt);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
};

#endif /* MONSTER_H_ */