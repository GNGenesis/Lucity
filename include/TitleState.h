#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Timer.h"
#include "Personality.h"

class TitleState : public State {

public:
	struct Option
	{
		std::string key;
		Vec2 pos;
		GameObject * selectorF;
		GameObject * selectorB;
		GameObject * button;
		bool selectable;
		int current;
	};

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
	void SetOption(std::vector<Option> menuOptions,int i = 0);
	bool SelectedOptionIs(std::vector<Option> menuOptions,std::string opt);

private:
	TileSet * set;
	Sprite * book;
	Sprite * effect;
	Sprite * effectF;
	Sprite * titleEsq;
	Sprite * titleDir;
	Sprite * press;
	Sprite * page;
	GameObject * settingsMenu;
	GameObject * go;
	std::vector<Personality> NPCList;
	std::vector<Option> menuOptions;
	std::vector<Option> settingOptions;
	std::vector<std::weak_ptr<GameObject>> settingsText;
	bool settingSelected = false;
	bool waitingKey = false;
	bool waitingEnter = false;
	bool waitingConfirm = false;
	int key;
	int frameCounter = 0;
	int frameCounterPage = 0;
	int currentOption = 0;
	int nLeft = SDLK_LEFT;
	int nRight=SDLK_RIGHT;
	int nUp=SDLK_UP;
	int nDown=SDLK_DOWN;
	int nPause = SDLK_p;
	int nBubbles = SDLK_1;
	int nFireball = SDLK_2;
	int nCapture = SDLK_3;
};

#endif /* TITLESTATE_H_ */
