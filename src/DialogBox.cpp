#include "DialogBox.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"

#include "Sprite.h"
#include "Text.h"
#include "CameraFollower.h"

DialogBox::DialogBox(GameObject& associated, std::string buttonSprite, std::string fontFile, std::string buttonName, Vec2 center, float secondsToSelfDesctruct) : Component(associated) {
	DialogBox::dialogSprite = buttonSprite;
	DialogBox::fontFile = fontFile;
	DialogBox::dialogName = buttonName;
	DialogBox::center = center;
	DialogBox::secondsToSelfDestruct = secondsToSelfDesctruct;

	sp = new Sprite(associated, buttonSprite);
	sp->SetScale(Vec2(5, 5));
	associated.AddComponent(sp);
	associated.AddComponent(new CameraFollower(associated, center - (associated.box.GetSize() / 2)));
}

DialogBox::~DialogBox() {

}

void DialogBox::Start() {
	GameObject* go = new GameObject();
	int i = sp->GetWidth() - 15;

	Sprite * bookTalking = new Sprite(*go, "assets/img/HUD/bookTalking.png", 5, 0.1, false);;
	bookTalking->SetScale(Vec2(3, 3));
	go->AddComponent(bookTalking);
	go->AddComponent(new CameraFollower(*go, center - (associated.box.GetSize()/2) - Vec2(90, -15)));
	book = Game::GetInstance().GetCurrentState().AddObject(go, "DIALOG");

	go = new GameObject();
	go->AddComponent(new Text(*go, fontFile, 20, dialogName, SDL_Color{}, Text::BLENDED, i));
	go->AddComponent(new CameraFollower(*go, center - (associated.box.GetSize() / 2) + Vec2(20, 15)));
	text = Game::GetInstance().GetCurrentState().AddObject(go, "DIALOG");
	if (!associated.IsActive()) {
		if (!text.expired())
			text.lock()->Deactivate();
		if (!book.expired())
			book.lock()->Deactivate();
	}
}

void DialogBox::Update(float dt) {
	if (secondsToSelfDestruct > 0) {
		selfDestructCount.Update(dt);
		if (selfDestructCount.Get() > secondsToSelfDestruct) {
			associated.RequestDelete();
			text.lock()->Deactivate();
			book.lock()->Deactivate();
		}
	}
}

void DialogBox::Activate() {
	Component::Activate();
	if (!text.expired())
		text.lock()->Activate();
	if (!book.expired())
		book.lock()->Activate();
}

void DialogBox::Deactivate() {
	Component::Deactivate();
	if (!text.expired())
		text.lock()->Deactivate();
	if (!book.expired())
		book.lock()->Deactivate();
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
std::weak_ptr<GameObject> DialogBox::GetSprite() {
	return book;
}
