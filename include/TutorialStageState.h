#ifndef TUTORIALSTAGESTATE_H_
#define TUTORIALSTAGESTATE_H_

#include "State.h"
#include "MonsterTutorial.h"
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
	Timer timer;
	Sprite* setas;
	GameObject* goSetas;
	GameObject* goDialog;
	GameObject* goBlib;
	GameObject* goSecondMonster;
	GameObject* goLastMonster;
	MonsterTutorial* blibMonster;
	Music backgroundMusic;
	std::vector<Personality> NPCList;
	std::vector<Personality> monsterList;
	int tutorialScene;
	int dialogScene;
	bool suitMoves;
	bool hudChecked;
	bool startDialog;

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
