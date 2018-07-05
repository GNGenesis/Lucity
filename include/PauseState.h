#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include "Timer.h"
#include "Personality.h"

class PauseState : public State {

public:
	PauseState();
	~PauseState();
	void LoadAssets();
	void Start();
	void Pause();
	void Resume();
	void DeletionCheck();
	void Update(float dt);
	void Render();
	void SetOption(int i = 0);
	bool SelectedOptionIs(std::string opt);

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

private:
	Sprite * book;
	GameObject * menu;
	std::vector<Option> menuOptions;
	int frameCounter = 0;
	int currentOption = 0;
};

#endif /* TITLESTATE_H_ */
#pragma once
