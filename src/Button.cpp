#include "Button.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"

#include "Sprite.h"
#include "Text.h"
#include "CameraFollower.h"

Button::Button(GameObject& associated, std::string buttonSprite, std::string fontFile, std::string buttonName, Vec2 center) : Component(associated){
	Button::buttonSprite = buttonSprite;
	Button::fontFile = fontFile;
	Button::buttonName = buttonName;
	Button::center = center;

	Sprite* sp = new Sprite(associated, buttonSprite);
	sp->SetScale(Vec2(3, 3));
	associated.AddComponent(sp);
	associated.AddComponent(new CameraFollower(associated, center-(associated.box.GetSize()/2)));
}

Button::~Button() {

}

void Button::Start() {
	GameObject* go = new GameObject();
	go->AddComponent(new Text(*go, fontFile, 25, buttonName, SDL_Color {}, Text::SOLID));
	go->AddComponent(new CameraFollower(*go, center-(go->box.GetSize()/2)));
	text = Game::GetInstance().GetCurrentState().AddObject(go, "MISC");
	if(!associated.IsActive())
		if(!text.expired())
			text.lock()->Deactivate();
}

void Button::Update(float dt) {
	selected = false;
	clicked = false;

	if(associated.box.Contains(InputManager::GetMousePos())) {
		selected = true;
	}
	if(InputManager::MousePress(LEFT_MOUSE_BUTTON)) {
		if(selected)
			clicked = true;
	}
	else if(InputManager::KeyPress(CONFIRM)) {
		clicked = true;
	}
}

void Button::Activate() {
	Component::Activate();
	clicked = false;
	if(!text.expired())
		text.lock()->Activate();
}

void Button::Deactivate() {
	Component::Deactivate();
	clicked = false;
	if(!text.expired())
		text.lock()->Deactivate();
}

void Button::SetText(std::string txt) {
	if(!text.expired()) {
		Text* t = (Text*) text.lock()->GetComponent("Text");
		if(t) {
			t->SetText(txt);
		}
	}
}

void Button::SetColor(SDL_Color color) {
	if(!text.expired()) {
		Text* t = (Text*) text.lock()->GetComponent("Text");
		if(t) {
			t->SetColor(color);
		}
	}
}

bool Button::Is(std::string type) {
	return (type == "Button");
}

bool Button::Selected() {
	return selected;
}

bool Button::Clicked() {
	return clicked;
}

std::weak_ptr<GameObject> Button::GetText() {
	return text;
}
