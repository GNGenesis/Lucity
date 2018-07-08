#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Timer.h"

class TitleState : public State {
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
	TitleState();
	~TitleState();
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

#endif /* TITLESTATE_H_ */
