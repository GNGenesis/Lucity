#include "Personality.h"

Personality::Personality() {
	Personality::name = "";
	Personality::nSpeed = 0;
	Personality::pSpeed = 0;
	Personality::idleT = 0;
	Personality::walkT = 0;
	Personality::shockT = 0;
	Personality::panicT = 0;
}

Personality::Personality(std::string name, int nSpeed, int pSpeed, float idleT, float walkT, float shockT, float panicT,
						 std::vector<std::string> fears, std::vector<std::string> interests) {
	Personality::name = name;
	Personality::nSpeed = nSpeed;
	Personality::pSpeed = pSpeed;
	Personality::idleT = idleT;
	Personality::walkT = walkT;
	Personality::shockT = shockT;
	Personality::panicT = panicT;
	Personality::fears = fears;
	Personality::interests = interests;
}

Personality::~Personality() {

}

std::string Personality::GetName() {
	return name;
}

int Personality::GetNormalSpeed() {
	return nSpeed;
}

int Personality::GetPanicSpeed() {
	return pSpeed;
}

float Personality::GetTime(std::string action) {
	if(action == "idle")
		return idleT;
	else if(action == "walk")
		return walkT;
	else if(action == "shock")
		return shockT;
	else if(action == "panic")
		return panicT;
	else
		return 0;
}

bool Personality::IsAfraid(std::string fear) {
	for(unsigned int i = 0; i < fears.size(); i++)
		if(fears[i] == fear)
			return true;
	return false;
}

bool Personality::IsInterested(std::string interest) {
	for(unsigned int i = 0; i < interests.size(); i++)
		if(interests[i] == interest)
			return true;
	return false;
}