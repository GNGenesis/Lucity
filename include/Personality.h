#ifndef PERSONALITY_H_
#define PERSONALITY_H_

#include "Vec2.h"

#include <string>
#include <vector>

class Personality {
private:
	std::string name;
	Vec2 speed;
	float idleT;
	float walkT;
	float shockT;
	float panicT;
	std::vector<std::string> fears;
	std::vector<std::string> interests;

public:
	Personality();
	Personality(std::string name, Vec2 speed, float idleT, float walkT, float shockT, float panicT);
	~Personality();
	std::string GetName();
	Vec2 GetSpeed();
	float GetTime(std::string action);
	bool IsAfraid(std::string fear);
	bool IsInterested(std::string interest);
};

#endif /* PERSONALITY_H_ */