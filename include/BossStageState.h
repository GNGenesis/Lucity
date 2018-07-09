#ifndef BOSSSTAGESTATE_H_
#define BOSSSTAGESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Timer.h"
#include "Personality.h"

#include "Boss.h"

#include <vector>

class BossStageState : public State {
private:
	Boss* boss;
	Timer rambleT;
	bool flipped;
	bool gameOver;
	TileSet* set;
	Music backgroundMusic;
	std::vector<Personality> NPCList;
	std::vector<Personality> monsterList;

public:
	BossStageState();
	~BossStageState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void Ramble();
	void Flip();
	void Clear();
	void CollisionCheck();
	void DeletionCheck();
	void Update(float dt);
	void Render();
};

#endif /* BOSSSTAGESTATE_H_ */