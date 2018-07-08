#ifndef TUTORIALSTAGESTATE_H_
#define TUTORIALSTAGESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Timer.h"
#include "Personality.h"

#include <vector>

class TutorialStageState : public State {
private:
	bool gameOver;
	TileSet* set;
	Music backgroundMusic;
	std::vector<Personality> NPCList;
	std::vector<Personality> monsterList;
	int tutorialScene;
	bool hudChecked;

public:
	TutorialStageState();
	~TutorialStageState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void CollisionCheck();
	void DeletionCheck();
	void Update(float dt);
	void LibrarianTutorialUpdate(float dt);
	void SecondMonsterTutorialUpdate(float dt);
	void FreeTutorialUpdate(float dt);
	void Render();
};

#endif /* TUTORIALSTAGESTATE_H_ */
