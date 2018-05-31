#include "Animator.h"

#include "Sprite.h"

#include "Player.h"

Animator::Animator(GameObject& associated, Character* character, std::string name) : Component(associated) {
	Animator::character = character;
	Animator::name = name;
}

Animator::~Animator() {
	sprites.clear();
}

void Animator::Start() {
	BuildSprites();
	for(auto& i: sprites)
		i.second->Deactivate();
	activeSprite = sprites["idleSE"];
	activeSprite->Activate();
}

void Animator::BuildSprites() {
	std::string path = "assets/img/characters/" + name;
	unsigned int idleFrames = 0;
	unsigned int walkFrames = 0;
	unsigned int shockFrames = 0;
	unsigned int panicFrames = 0;
	unsigned int attackFrames = 0;
	
	if(associated.GetComponent("Player")) {
		idleFrames = 4;
		walkFrames = 4;
		attackFrames = 4;

		sprites.emplace("attackNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackNW.png", attackFrames, 0.1)));
		sprites.emplace("attackNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackNE.png", attackFrames, 0.1)));
		sprites.emplace("attackSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackSW.png", attackFrames, 0.1)));
		sprites.emplace("attackSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackSE.png", attackFrames, 0.1)));
	}
	else {
		if(name == "girl") {
			idleFrames = 4;
			walkFrames = 4;
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

		sprites.emplace("shockNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNW.png", idleFrames, 0.2)));
		sprites.emplace("shockNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNE.png", idleFrames, 0.2)));
		sprites.emplace("shockSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSW.png", idleFrames, 0.2)));
		sprites.emplace("shockSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSE.png", idleFrames, 0.2)));

		sprites.emplace("panicNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicNW.png", panicFrames, 0.12)));
		sprites.emplace("panicNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicNE.png", panicFrames, 0.12)));
		sprites.emplace("panicSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicSW.png", panicFrames, 0.12)));
		sprites.emplace("panicSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicSE.png", panicFrames, 0.12)));

		if(associated.GetComponent("Monster")) {
			std::string monsterPath = "assets/img/characters/monster";
			sprites.emplace("mIdleNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idle.png")));
			sprites.emplace("mIdleNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idle.png")));
			sprites.emplace("mIdleSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idle.png")));
			sprites.emplace("mIdleSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idle.png")));
			sprites.emplace("mWalkNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idle.png")));
			sprites.emplace("mWalkNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idle.png")));
			sprites.emplace("mWalkSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idle.png")));
			sprites.emplace("mWalkSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idle.png")));
			//sprites.emplace("mIdleNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleNW.png", idleFrames, 0.2)));
			//sprites.emplace("mIdleNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleNE.png", idleFrames, 0.2)));
			//sprites.emplace("mIdleSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleSW.png", idleFrames, 0.2)));
			//sprites.emplace("mIdleSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleSE.png", idleFrames, 0.2)));
			//sprites.emplace("mWalkNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkNW.png", walkFrames, 0.2)));
			//sprites.emplace("mWalkNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkNE.png", walkFrames, 0.2)));
			//sprites.emplace("mWalkSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkSW.png", walkFrames, 0.2)));
			//sprites.emplace("mWalkSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkSE.png", walkFrames, 0.2)));
		}
	}

	sprites.emplace("idleNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNW.png", idleFrames, 0.2)));
	sprites.emplace("idleNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNE.png", idleFrames, 0.2)));
	sprites.emplace("idleSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSW.png", idleFrames, 0.2)));
	sprites.emplace("idleSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSE.png", idleFrames, 0.2)));

	sprites.emplace("walkNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/walkNW.png", walkFrames, 0.2)));
	sprites.emplace("walkNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/walkNE.png", walkFrames, 0.2)));
	sprites.emplace("walkSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/walkSW.png", walkFrames, 0.2)));
	sprites.emplace("walkSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/walkSE.png", walkFrames, 0.2)));
	
	for(auto& i: sprites)
		i.second->SetScale(Vec2(2, 2));
}

void Animator::Update(float dt) {
	if(sprites.count(character->GetSprite())) {
		if(sprites[character->GetSprite()] != activeSprite) {
			activeSprite->Deactivate();
			activeSprite = sprites[character->GetSprite()];
			Sprite* sp = (Sprite*) activeSprite;
			Vec2 center = associated.box.GetCenter();
			associated.box.SetSize(Vec2(sp->GetWidth(), sp->GetHeight()));
			associated.box.SetCenter(center);
			activeSprite->Activate();
		}
	}
}

void Animator::Render() {

}

bool Animator::Is(std::string type) {
	return (type == "Animator");
}
