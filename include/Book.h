#ifndef BOOK_H_
#define BOOK_H_

#include "Component.h"
#include "Timer.h"

#include <string>

class Book : public Component {
private:
	std::weak_ptr<GameObject> player;
	std::string attackMode;
	std::string direction;
	std::string action;
	float arc;

	Timer actionT;
	float openCD;
	float channelCD;
	float closeCD;
	bool attacking;

	Timer executeT;
	float executeCD;
	bool executing;

public:
	Book(GameObject& associated, GameObject& player);
	~Book();
	void Start();
	void SetArc(float arc);
	void SetAction(std::string action);
	void SetDirection(std::string direction);
	void SetAttackMode(std::string attackMode);
	void ModeSwitch(int scroll);
	void Update(float dt);
	bool Is(std::string type);
	bool Attacking();
	float GetArc();
	std::string GetSprite();
	std::string GetAction();
	std::string GetDirection();
	std::string GetAttackMode();
};

#endif /* BOOK_H_ */