#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Personality.h"
#include "Timer.h"

class TitleState : public State {
private:
	std::vector<Personality> NPCList;
public:
	TitleState();
	~TitleState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void Update(float dt);
	void Render();
};

#endif /* TITLESTATE_H_ */
