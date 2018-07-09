#include "BookAnimator.h"

BookAnimator::BookAnimator(GameObject& associated, Book* book) : Component(associated) {
	BookAnimator::book = book;
	action = "";
}

BookAnimator::~BookAnimator() {
	sprites.clear();
}

void BookAnimator::Start() {
	BuildSprites();
	for(auto& i: sprites)
		i.second->Deactivate();
	activeSprite = sprites["idleSE"];
	activeSprite->Activate();
}

void BookAnimator::BuildSprites() {
	std::string path = "assets/img/characters/book";

	sprites.emplace("idleNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNW.png")));
	sprites.emplace("idleNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNE.png")));
	sprites.emplace("idleSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSW.png")));
	sprites.emplace("idleSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSE.png")));

	sprites.emplace("openNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/openNW.png", 4, 0.1, false)));
	sprites.emplace("openNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/openNE.png", 4, 0.1, false)));
	sprites.emplace("openSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/openSW.png", 4, 0.1, false)));
	sprites.emplace("openSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/openSE.png", 4, 0.1, false)));

	sprites.emplace("channelNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/channelNW.png", 5, 0.05)));
	sprites.emplace("channelNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/channelNE.png", 5, 0.05)));
	sprites.emplace("channelSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/channelSW.png", 5, 0.05)));
	sprites.emplace("channelSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/channelSE.png", 5, 0.05)));

	sprites.emplace("closeNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/closeNW.png", 4, 0.1, false)));
	sprites.emplace("closeNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/closeNE.png", 4, 0.1, false)));
	sprites.emplace("closeSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/closeSW.png", 4, 0.1, false)));
	sprites.emplace("closeSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/closeSE.png", 4, 0.1, false)));

	for(auto& i: sprites)
		i.second->SetScale(Vec2(2, 2));
}


void BookAnimator::Update(float dt) {
	if(sprites.count(book->GetSprite())) {
		if(sprites[book->GetSprite()] != activeSprite) {
			activeSprite->Deactivate();
			int frame = 0;
			float time = 0;
			if(book->GetAction() == action) {
				frame = activeSprite->GetFrame();
				time = activeSprite->GetTime();
			}
			action = book->GetAction();
			activeSprite = sprites[book->GetSprite()];
			activeSprite->SetFrame(frame);
			activeSprite->SetTime(time);
			Vec2 pos = associated.box.GetPos();
			Vec2 size = associated.box.GetSize();
			Vec2 newSize = activeSprite->GetSize();
			Vec2 center = associated.box.GetCenter();
			associated.box.SetSize(newSize);
			associated.box.SetCenter(center.x, pos.y+size.y-newSize.y/2);
			activeSprite->Activate();
		}
	}
}

bool BookAnimator::Is(std::string type) {
	return (type == "BookAnimator");
}
