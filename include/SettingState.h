#ifndef SETTINGSTATE_H_
#define SETTINGSTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Timer.h"
#include "Personality.h"

class SettingState : public State {

public:
	struct Option
	{
		std::string key;
		Vec2 pos;
		GameObject * selectorF;
		GameObject * selectorB;
		GameObject * text;
		bool selectable;
		int current;
	};

	SettingState();
	~SettingState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void CollisionCheck();
	void DeletionCheck();
	void Update(float dt);
	void Render();
	void SetOption(std::vector<Option> menuOptions, int i = 0);
	bool SelectedOptionIs(std::vector<Option> menuOptions, std::string opt);

private:
	TileSet * set;
	Sprite * book;
	Sprite * page;
	Sprite * effect;
	GameObject * goBook;
	GameObject * settingsMenu;
	GameObject * go;
	std::vector<Personality> NPCList;
	std::vector<Option> menuOptions;
	std::vector<Option> settingOptions;
	std::vector<std::weak_ptr<GameObject>> settingsText;
	std::vector<std::weak_ptr<Component>> scaleComponents;
	bool controllerSelected = false;
	bool ScreenSelected = false;
	bool waitingKey = false;
	bool waitingEnter = false;
	bool waitingConfirm = false;
	int key;
	int frameCounter = 0;
	int frameCounterPage = 0;
	int currentOption = 0;
	int nLeft = SDLK_LEFT;
	int nRight = SDLK_RIGHT;
	int nUp = SDLK_UP;
	int nDown = SDLK_DOWN;
	int nPause = SDLK_p;
	int nBubbles = SDLK_1;
	int nFireball = SDLK_2;
	int nCapture = SDLK_3;
};

#endif /* TITLESTATE_H_ */
