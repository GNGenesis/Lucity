#ifndef ENDSTATE_H_
#define ENDSTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"

class EndState : public State {
private:
	GameObject* bg;
	GameObject* txt;
	Music backgroundMusic;

public:
	EndState();
	~EndState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void Update(float dt);
	void Render();
};

#endif /* ENDSTATE_H_ */
