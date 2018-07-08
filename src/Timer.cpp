#include "Timer.h"

#include <algorithm>

Timer::Timer() {
	time = 0;
}

Timer::~Timer() {

}

void Timer::Update(float dt) {
	time += dt;
}

void Timer::Restart() {
	time = 0;
}

float Timer::Get() {
	return time;
}
