#ifndef STAGESTATE_H_
#define STAGESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"

class StageState : public State {
private:
	GameObject* bg;
	GameObject* map;
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

#endif /* STAGESTATE_H_ */
