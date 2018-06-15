/*#ifndef BOSSSTATE_H_
#define BOSSSTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"

class StageState : public State {
private:
	TileSet* set;
	Music backgroundMusic;

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

#endif*/ /* BOSSSTATE_H_ */
