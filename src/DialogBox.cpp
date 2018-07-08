#include "DialogBox.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"

#include "Sprite.h"
#include "Text.h"
#include "CameraFollower.h"

DialogBox::DialogBox(GameObject& associated, std::string buttonSprite, std::string fontFile, std::string buttonName, Vec2 center) : Component(associated) {
	DialogBox::dialogSprite = buttonSprite;
	DialogBox::fontFile = fontFile;
	DialogBox::dialogName = buttonName;
	DialogBox::center = center;

	sp = new Sprite(associated, buttonSprite);
	sp->SetScale(Vec2(5, 5));
	associated.AddComponent(sp);
	associated.AddComponent(new CameraFollower(associated, center - (associated.box.GetSize() / 2)));
}

DialogBox::~DialogBox() {

}

void DialogBox::Start() {
	GameObject* go = new GameObject();
	int i = sp->GetWidth();
	go->AddComponent(new Text(*go, fontFile, 15, dialogName, SDL_Color{}, Text::BLENDED, i));
	go->AddComponent(new CameraFollower(*go,  center - (associated.box.GetSize() / 2) + Vec2(5,5)));
	text = Game::GetInstance().GetCurrentState().AddObject(go, "GUI");
	if (!associated.IsActive())
		if (!text.expired())
			text.lock()->Deactivate();
}

void DialogBox::Update(float dt) {

}

void DialogBox::Activate() {
	Component::Activate();
	if (!text.expired())
		text.lock()->Activate();
}

void DialogBox::Deactivate() {
	Component::Deactivate();
	if (!text.expired())
		text.lock()->Deactivate();
}

void DialogBox::SetText(std::string txt) {
	if (!text.expired()) {
		Text* t = (Text*)text.lock()->GetComponent("Text");
		if (t) {
			t->SetText(txt);
		}
	}
}

void DialogBox::SetColor(SDL_Color color) {
	if (!text.expired()) {
		Text* t = (Text*)text.lock()->GetComponent("Text");
		if (t) {
			t->SetColor(color);
		}
	}
}

bool DialogBox::Is(std::string type) {
	return (type == "DialogBox");
}

std::weak_ptr<GameObject> DialogBox::GetText() {
	return text;
}
