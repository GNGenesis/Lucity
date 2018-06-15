#ifndef BOSSSTAGESTATE_H_
#define BOSSSTAGESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Personality.h"

#include <vector>

class BossStageState : public State {
private:
	Timer  rambleT;
	TileSet * set;
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
	void CollisionCheck();
	void DeletionCheck();
	void Update(float dt);
	void Render();
	void Ramble();
};

#endif /* STAGESTATE_H_ */
