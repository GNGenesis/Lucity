#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Timer.h"
#include "Personality.h"

#include <vector>

class StageState : public State {
private:
	bool gameOver;
	TileSet* set;
	Music backgroundMusic;
	std::vector<Personality> NPCList;
	std::vector<Personality> monsterList;

public:
	StageState();
	~StageState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void CollisionCheck();
	void DeletionCheck();
	void Update(float dt);
	void Render();
};

#endif /* STAGESTATE_H_ */
