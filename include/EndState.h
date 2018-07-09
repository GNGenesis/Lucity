#ifndef ENDSTATE_H_
#define ENDSTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Timer.h"

class EndState : public State {
private:
	Timer animationT;
	int animationCount;

public:
	EndState();
	~EndState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void Opening();
	void Update(float dt);
	void Render();
};

#endif /* ENDSTATE_H_ */