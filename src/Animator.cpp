#include "Animator.h"

Animator::Animator(GameObject& associated, Character* character, std::string name) : Component(associated) {
	Animator::character = character;
	Animator::action = "";
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

	if(associated.GetComponent("Player")) {
		idleFrames = 4;
		walkFrames = 4;

		sprites.emplace("attackNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackNW.png", 4, 0.1)));
		sprites.emplace("attackNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackNE.png", 4, 0.1)));
		sprites.emplace("attackSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackSW.png", 4, 0.1)));
		sprites.emplace("attackSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/attackSE.png", 4, 0.1)));
	}
	else if(associated.GetComponent("NPC")) {
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
		else if (name == "blib") {
			idleFrames = 4;
			walkFrames = 4;
		}

		if (name != "blib") {
			sprites.emplace("shockNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNW.png", shockFrames, 0.2)));
			sprites.emplace("shockNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleNE.png", shockFrames, 0.2)));
			sprites.emplace("shockSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSW.png", shockFrames, 0.2)));
			sprites.emplace("shockSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/idleSE.png", shockFrames, 0.2)));

			sprites.emplace("panicNW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicNW.png", panicFrames, 0.2)));
			sprites.emplace("panicNE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicNE.png", panicFrames, 0.2)));
			sprites.emplace("panicSW", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicSW.png", panicFrames, 0.2)));
			sprites.emplace("panicSE", (Sprite*)associated.AddComponent(new Sprite(associated, path+"/panicSE.png", panicFrames, 0.2)));
		}

		if(associated.GetComponent("Monster")) {
			std::string monsterPath = "assets/img/characters/monster";

			sprites.emplace("mTransformSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/transformSE.png", 7, 0.12)));

			sprites.emplace("mStunNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stunNW.png", 4, 0.2)));
			sprites.emplace("mStunNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stunNE.png", 4, 0.2)));
			sprites.emplace("mStunSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stunSW.png", 4, 0.2)));
			sprites.emplace("mStunSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stunSE.png", 4, 0.2)));

			sprites.emplace("mIdleNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleNW.png", 6, 0.2)));
			sprites.emplace("mIdleNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleNE.png", 6, 0.2)));
			sprites.emplace("mIdleSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleSW.png", 6, 0.2)));
			sprites.emplace("mIdleSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleSE.png", 6, 0.2)));

			sprites.emplace("hurt/mIdleNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/idleNW.png", 6, 0.2)));
			sprites.emplace("hurt/mIdleNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/idleNE.png", 6, 0.2)));
			sprites.emplace("hurt/mIdleSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/idleSW.png", 6, 0.2)));
			sprites.emplace("hurt/mIdleSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/idleSE.png", 6, 0.2)));

			sprites.emplace("mWalkNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkNW.png", 4, 0.2)));
			sprites.emplace("mWalkNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkNE.png", 4, 0.2)));
			sprites.emplace("mWalkSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkSW.png", 4, 0.2)));
			sprites.emplace("mWalkSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkSE.png", 4, 0.2)));

			sprites.emplace("hurt/mWalkNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/walkNW.png", 4, 0.2)));
			sprites.emplace("hurt/mWalkNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/walkNE.png", 4, 0.2)));
			sprites.emplace("hurt/mWalkSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/walkSW.png", 4, 0.2)));
			sprites.emplace("hurt/mWalkSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/walkSE.png", 4, 0.2)));

			sprites.emplace("mAttackNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/attackNW.png", 7, 0.14)));
			sprites.emplace("mAttackNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/attackNE.png", 7, 0.14)));
			sprites.emplace("mAttackSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/attackSW.png", 7, 0.14)));
			sprites.emplace("mAttackSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/attackSE.png", 7, 0.14)));

			sprites.emplace("hurt/mAttackNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/attackNW.png", 7, 0.14)));
			sprites.emplace("hurt/mAttackNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/attackNE.png", 7, 0.14)));
			sprites.emplace("hurt/mAttackSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/attackSW.png", 7, 0.14)));
			sprites.emplace("hurt/mAttackSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/attackSE.png", 7, 0.14)));
		}
		else if (associated.GetComponent("TutorialLibrarian")) {
			std::string monsterPath = "assets/img/characters/monster";

			sprites.emplace("mTransformSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/transformSE.png", 7, 0.12)));

			sprites.emplace("mStunNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stunNW.png", 4, 0.2)));
			sprites.emplace("mStunNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stunNE.png", 4, 0.2)));
			sprites.emplace("mStunSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stunSW.png", 4, 0.2)));
			sprites.emplace("mStunSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/stunSE.png", 4, 0.2)));

			sprites.emplace("mIdleNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleNW.png", 6, 0.2)));
			sprites.emplace("mIdleNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleNE.png", 6, 0.2)));
			sprites.emplace("mIdleSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleSW.png", 6, 0.2)));
			sprites.emplace("mIdleSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/idleSE.png", 6, 0.2)));

			sprites.emplace("hurt/mIdleNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/idleNW.png", 6, 0.2)));
			sprites.emplace("hurt/mIdleNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/idleNE.png", 6, 0.2)));
			sprites.emplace("hurt/mIdleSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/idleSW.png", 6, 0.2)));
			sprites.emplace("hurt/mIdleSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/idleSE.png", 6, 0.2)));

			sprites.emplace("mWalkNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkNW.png", 4, 0.2)));
			sprites.emplace("mWalkNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkNE.png", 4, 0.2)));
			sprites.emplace("mWalkSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkSW.png", 4, 0.2)));
			sprites.emplace("mWalkSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/walkSE.png", 4, 0.2)));

			sprites.emplace("hurt/mWalkNW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/walkNW.png", 4, 0.2)));
			sprites.emplace("hurt/mWalkNE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/walkNE.png", 4, 0.2)));
			sprites.emplace("hurt/mWalkSW", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/walkSW.png", 4, 0.2)));
			sprites.emplace("hurt/mWalkSE", (Sprite*)associated.AddComponent(new Sprite(associated, monsterPath+"/hurt/walkSE.png", 4, 0.2)));
		}
		else if(associated.GetComponent("Boss")) {
			std::string bossPath = "assets/img/characters/boss";

			sprites.emplace("bTransform", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/transform.png", 6, 0.12)));

			sprites.emplace("bStunNW", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/stunNW.png", 4, 0.2)));
			sprites.emplace("bStunNE", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/stunNE.png", 4, 0.2)));
			sprites.emplace("bStunSW", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/stunSW.png", 4, 0.2)));
			sprites.emplace("bStunSE", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/stunSE.png", 4, 0.2)));

			sprites.emplace("bIdleNW", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/idleNW.png", 4, 0.2)));
			sprites.emplace("bIdleNE", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/idleNE.png", 4, 0.2)));
			sprites.emplace("bIdleSW", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/idleSW.png", 4, 0.2)));
			sprites.emplace("bIdleSE", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/idleSE.png", 4, 0.2)));

			sprites.emplace("bAttackNW", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/attackNW.png", 4, 0.2)));
			sprites.emplace("bAttackNE", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/attackNE.png", 4, 0.2)));
			sprites.emplace("bAttackSW", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/attackSW.png", 4, 0.2)));
			sprites.emplace("bAttackSE", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/attackSE.png", 4, 0.2)));

			sprites.emplace("bHurtNW", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/hurtSE.png", 4, 0.2)));
			sprites.emplace("bHurtNE", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/hurtSE.png", 4, 0.2)));
			sprites.emplace("bHurtSW", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/hurtSE.png", 4, 0.2)));
			sprites.emplace("bHurtSE", (Sprite*)associated.AddComponent(new Sprite(associated, bossPath+"/hurtSE.png", 4, 0.2)));
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

	if(associated.GetComponent("Player")) {
		idleFrames = 4;
		walkFrames = 4;

		sprites["attackNW"]->Open(path+"/attackNW.png", 4, 0.1);
		sprites["attackNE"]->Open(path+"/attackNE.png", 4, 0.1);
		sprites["attackSW"]->Open(path+"/attackSW.png", 4, 0.1);
		sprites["attackSE"]->Open(path+"/attackSE.png", 4, 0.1);
	}
	else if(associated.GetComponent("NPC")) {
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
			int frame = 0;
			float time = 0;
			if(character->GetAction() == action) {
				frame = activeSprite->GetFrame();
				time = activeSprite->GetTime();
			}
			action = character->GetAction();
			activeSprite = sprites[character->GetSprite()];
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

bool Animator::Is(std::string type) {
	return (type == "Animator");
}
