#ifndef TIMER_H_
#define TIMER_H_

class Timer {
private:
	float time;

public:
	Timer();
	~Timer();
	void Update(float dt);
	void Restart();
	float Get();
};

#endif /* TIMER_H_ */
