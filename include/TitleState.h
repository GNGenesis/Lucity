#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Timer.h"
#include "Personality.h"

class TitleState : public State {
private:
	TileSet* set;
	std::vector<Personality> NPCList;

public:
	TitleState();
	~TitleState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void CollisionCheck();
	void DeletionCheck();
	void Update(float dt);
	void Render();
};

#endif /* TITLESTATE_H_ */
