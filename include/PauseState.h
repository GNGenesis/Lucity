#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Timer.h"

class PauseState : public State {
private:
	Timer animationT;
	int animationCount;

	std::unordered_map<std::string, std::vector<std::weak_ptr<GameObject>>> buttons;
	std::weak_ptr<GameObject> selected;
	std::string layer;
	int index;

	int enteredKey;
	bool waitingKey;
	bool waitingConfirmation;

public:
	PauseState();
	~PauseState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void Opening();
	void Passing();
	void SetKey();
	void Navigate();
	void ExecuteButton();
	void Update(float dt);
	void Render();
};

#endif /* PAUSESTATE_H_ */
