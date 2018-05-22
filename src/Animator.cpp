#include "Animator.h"

#include "Sprite.h"

Animator::Animator(GameObject& associated, Character* character, std::string name) : Component(associated) {
	Animator::character = character;
	Animator::name = name;
	BuildSprites();
	for(auto& i: sprites)
		i.second->Deactivate();
	activeSprite = sprites["idleSE"];
	activeSprite->Activate();
}

Animator::~Animator() {
	sprites.clear();
}

void Animator::BuildSprites() {
	std::string path = "assets/img/characters/"+name;
	unsigned int idleFrames;
	unsigned int walkFrames;
	unsigned int panicFrames;
	
	if(name == "lucas") {
		idleFrames = 4;
		walkFrames = 4;
		sprites.emplace("attackNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackNW.png", 4, 0.12)));
		sprites.emplace("attackNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackNE.png", 4, 0.12)));
		sprites.emplace("attackSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackSW.png", 4, 0.12)));
		sprites.emplace("attackSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackSE.png", 4, 0.12)));
	}
	else {
		if(name == "girl") {
			idleFrames = 4;
			walkFrames = 5;
			panicFrames = 4;
		}
		else if(name == "luv") {
			idleFrames = 4;
			walkFrames = 4;
			panicFrames = 4;
		}
		else if(name == "old") {
			idleFrames = 4;
			walkFrames = 3;
			panicFrames = 4;
		}
		else if(name == "suit") {
			idleFrames = 4;
			walkFrames = 4;
			panicFrames = 4;
		}
		sprites.emplace("panicNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicNW.png", panicFrames, 0.12)));
		sprites.emplace("panicNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicNE.png", panicFrames, 0.12)));
		sprites.emplace("panicSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicSW.png", panicFrames, 0.12)));
		sprites.emplace("panicSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicSE.png", panicFrames, 0.12)));
	}

	sprites.emplace("idleNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNW.png", idleFrames, 0.2)));
	sprites.emplace("idleNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNE.png", idleFrames, 0.2)));
	sprites.emplace("idleSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSW.png", idleFrames, 0.2)));
	sprites.emplace("idleSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSE.png", idleFrames, 0.2)));
	sprites.emplace("walkNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/walkNW.png", walkFrames, 0.12)));
	sprites.emplace("walkNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/walkNE.png", walkFrames, 0.12)));
	sprites.emplace("walkSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/walkSW.png", walkFrames, 0.12)));
	sprites.emplace("walkSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/walkSE.png", walkFrames, 0.12)));
	
	for(auto& i: sprites)
		i.second->SetScale(Vec2(2, 2));
}

void Animator::Update(float dt) {
	if(sprites.count(character->GetSprite())) {
		if(sprites[character->GetSprite()] != activeSprite) {
			activeSprite->Deactivate();
			activeSprite = sprites[character->GetSprite()];
			Sprite* sp = (Sprite*) activeSprite;
			associated.box.SetSize(Vec2(sp->GetWidth(), sp->GetHeight()));
			activeSprite->Activate();
		}
	}
}

void Animator::Render() {

}

bool Animator::Is(std::string type) {
	return (type == "Animator");
}
