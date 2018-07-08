#ifndef TUTORIALSTATESTATE_H_
#define TUTORIALSTATESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Timer.h"
#include "Personality.h"

#include <vector>

class TutorialState : public State {
private:
	bool gameOver;
	TileSet* set;
	Music backgroundMusic;
	std::vector<Personality> NPCList;
	std::vector<Personality> monsterList;

public:
	TutorialState();
	~TutorialState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void CollisionCheck();
	void DeletionCheck();
	void Update(float dt);
	void Render();
};

#endif /* TUTORIALSTATESTATE_H_ */
