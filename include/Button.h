#ifndef BUTTON_H_
#define BUTTON_H_

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"

#include <string>
#include <memory>

class Button : public Component {
private:
	std::weak_ptr<GameObject> text;
	std::string buttonSprite;
	std::string fontFile;
	std::string buttonName;
	Vec2 center;
	bool selected;
	bool clicked;

public:
	Button(GameObject& associated, std::string buttonSprite, std::string fontFile, std::string buttonName, Vec2 center);
	~Button();
	void Start();
	void Update(float dt);
	void Activate();
	void Deactivate();
	void SetText(std::string txt);
	void SetColor(SDL_Color color);
	bool Is(std::string type);
	bool Selected();
	bool Clicked();
	std::weak_ptr<GameObject> GetText();
};

#endif /* BUTTON_H_ */