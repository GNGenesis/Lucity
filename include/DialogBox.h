#ifndef DIALOGBOX_H_
#define DIALOGBOX_H_

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"
#include "Sprite.h"

#include <string>
#include <memory>

class DialogBox : public Component {
private:
	std::weak_ptr<GameObject> text;
	std::weak_ptr<GameObject> book;
	std::string dialogSprite;
	std::string fontFile;
	std::string dialogName;
	Timer selfDestructCount;
	float secondsToSelfDestruct;
	Sprite * sp;
	Vec2 center;

public:
	DialogBox(GameObject& associated, std::string buttonSprite, std::string fontFile, std::string buttonName, Vec2 center, float secondsToSelfDesctruct = 0);
	~DialogBox();
	void Start();
	void Update(float dt);
	void Activate();
	void Deactivate();
	void SetText(std::string txt);
	void SetColor(SDL_Color color);
	bool Is(std::string type);
	std::weak_ptr<GameObject> GetText();
	std::weak_ptr<GameObject> GetSprite();
};

#endif /* BUTTON_H_ */