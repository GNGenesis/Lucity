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
			shockFrames = 4;
			panicFrames = 4;
		}
		else if(name == "hobo") {
			idleFrames = 4;
			walkFrames = 4;
			shockFrames = 4;
			panicFrames = 4;
		}
		else if(name == "luv") {
			idleFrames = 4;
			walkFrames = 4;
			shockFrames = 4;
			panicFrames = 4;
		}
		else if(name == "old") {
			idleFrames = 4;
			walkFrames = 3;
			shockFrames = 4;
			panicFrames = 4;
		}
		else if(name == "suit") {
			idleFrames = 4;
			walkFrames = 4;
			shockFrames = 4;
			panicFrames = 4;
		}

		sprites.emplace("shockNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNW.png", shockFrames, 0.2)));
		sprites.emplace("shockNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNE.png", shockFrames, 0.2)));
		sprites.emplace("shockSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSW.png", shockFrames, 0.2)));
		sprites.emplace("shockSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSE.png", shockFrames, 0.2)));

		sprites.emplace("panicNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicNW.png", panicFrames, 0.2)));
		sprites.emplace("panicNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicNE.png", panicFrames, 0.2)));
		sprites.emplace("panicSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicSW.png", panicFrames, 0.2)));
		sprites.emplace("panicSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicSE.png", panicFrames, 0.2)));

		if(associated.GetComponent("Monster")) {
			std::string monsterPath = "assets/img/characters/monster";

			sprites.emplace("mTransform", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/transform.png", 7, 0.2)));

			sprites.emplace("mStun", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stun.png", 3, 0.2)));

			sprites.emplace("mIdleNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleNW.png", 3, 0.16)));
			sprites.emplace("mIdleNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleNE.png", 3, 0.16)));
			sprites.emplace("mIdleSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleSW.png", 3, 0.16)));
			sprites.emplace("mIdleSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleSE.png", 3, 0.16)));
			
			sprites.emplace("mWalkNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkNW.png", 5, 0.16)));
			sprites.emplace("mWalkNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkNE.png", 5, 0.16)));
			sprites.emplace("mWalkSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkSW.png", 5, 0.16)));
			sprites.emplace("mWalkSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkSE.png", 5, 0.16)));
			
			sprites.emplace("mAttackNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/attackNW.png", 3, 0.16)));
			sprites.emplace("mAttackNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/attackNE.png", 3, 0.16)));
			sprites.emplace("mAttackSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/attackSW.png", 3, 0.16)));
			sprites.emplace("mAttackSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/attackSE.png", 3, 0.16)));
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

void Animator::RebuildSprites(std::string name) {
	Animator::name = name;
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

		sprites["attackNW"]->Open(path+"/attackNW.png", attackFrames, 0.1);
		sprites["attackNE"]->Open(path+"/attackNE.png", attackFrames, 0.1);
		sprites["attackSW"]->Open(path+"/attackSW.png", attackFrames, 0.1);
		sprites["attackSE"]->Open(path+"/attackSE.png", attackFrames, 0.1);
	}
	else {
		if(name == "girl") {
			idleFrames = 4;
			walkFrames = 4;
			shockFrames = 4;
			panicFrames = 4;
		}
		else if(name == "hobo") {
			idleFrames = 4;
			walkFrames = 4;
			shockFrames = 4;
			panicFrames = 4;
		}
		else if(name == "luv") {
			idleFrames = 4;
			walkFrames = 4;
			shockFrames = 4;
			panicFrames = 4;
		}
		else if(name == "old") {
			idleFrames = 4;
			walkFrames = 3;
			shockFrames = 4;
			panicFrames = 4;
		}
		else if(name == "suit") {
			idleFrames = 4;
			walkFrames = 4;
			shockFrames = 4;
			panicFrames = 4;
		}

		sprites["shockNW"]->Open(path+"/idleNW.png", shockFrames, 0.2);
		sprites["shockNE"]->Open(path+"/idleNE.png", shockFrames, 0.2);
		sprites["shockSW"]->Open(path+"/idleSW.png", shockFrames, 0.2);
		sprites["shockSE"]->Open(path+"/idleSE.png", shockFrames, 0.2);

		sprites["panicNW"]->Open(path+"/panicNW.png", panicFrames, 0.2);
		sprites["panicNE"]->Open(path+"/panicNE.png", panicFrames, 0.2);
		sprites["panicSW"]->Open(path+"/panicSW.png", panicFrames, 0.2);
		sprites["panicSE"]->Open(path+"/panicSE.png", panicFrames, 0.2);
	}

	sprites["idleNW"]->Open(path+"/idleNW.png", idleFrames, 0.2);
	sprites["idleNE"]->Open(path+"/idleNE.png", idleFrames, 0.2);
	sprites["idleSW"]->Open(path+"/idleSW.png", idleFrames, 0.2);
	sprites["idleSE"]->Open(path+"/idleSE.png", idleFrames, 0.2);

	sprites["walkNW"]->Open(path+"/walkNW.png", walkFrames, 0.2);
	sprites["walkNE"]->Open(path+"/walkNE.png", walkFrames, 0.2);
	sprites["walkSW"]->Open(path+"/walkSW.png", walkFrames, 0.2);
	sprites["walkSE"]->Open(path+"/walkSE.png", walkFrames, 0.2);
	
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
