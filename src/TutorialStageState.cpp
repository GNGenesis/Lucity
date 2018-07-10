#include "TutorialStageState.h"
#include "StageState.h"
#include "PauseState.h"
#include "EndState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "DialogBox.h"
#include "Sprite.h"
#include "Monster.h"
#include "Sound.h"
#include "Text.h"
#include "HUD.h"
#include "TileMap.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "MainObject.h"

#include "Player.h"
#include "NPCTutorial.h"
#include "MonsterTutorial.h"

#include <algorithm>

bool SortRenderOrderTutorial_MS(std::shared_ptr<GameObject> i, std::shared_ptr<GameObject> j) {
	return (i->box.y < j->box.y);
}

TutorialStageState::TutorialStageState() : State() {
	tutorialScene = 0;
	gameOver = false;
	GameData::eventCD = 5;
	startDialog = false;
	hudChecked = false;
	suitMoves = false;
	suitDialog = false;
	dialogScene = 0;

	GameObject* go;

	NPCList.emplace_back(Personality("girl", 150, 200, 1, 3, 1, 3, { "hobo" }, { "suit", "tree" }));
	NPCList.emplace_back(Personality("hobo", 150, 150, 2, 2, 1, 2, {}, { "suit", "trashcan" }));
	NPCList.emplace_back(Personality("luv", 150, 50, 3, 1, 2, 2, { "old" }, { "girl", "suit" }));
	NPCList.emplace_back(Personality("old", 50, 250, 3, 1, 1.5, 2, {}, { "luv", "bench" }));

	monsterList.emplace_back(Personality("girl", 50, 200, 0.3, 5, 1, 1, { "luv" }, { "hobo" }));
	monsterList.emplace_back(Personality("hobo", 250, 50, 1, 3, 3, 1, {}, { "girl", "luv", "old", "suit" }));
	monsterList.emplace_back(Personality("luv", 150, 150, 10, 2, 1, 2, {}, { "old", "tree" }));
	monsterList.emplace_back(Personality("old", 300, 250, 1, 2, 2, 2, { "tree" }, { "trashcan" }));

	//TileMap
	go = new GameObject();
	set = new TileSet(*go, "assets/img/cenario/biblioteca/tilesbiblioteca.png", 64, 64);
	TileMap* map = new TileMap(*go, set, "assets/map/tileMapBiblioteca.txt");
	go->AddComponent(map);
	go->box.SetSize(Vec2());
	AddObject(go, "BG");

	int mw = 64 * map->GetWidth();
	int mh = 64 * map->GetHeight();
	GameData::mapSize = Vec2(mw, mh);
	GameData::upperLimit = 100;

	//HUD
	go = new GameObject();
	go->AddComponent(new HUD(*go));
	go->AddComponent(new CameraFollower(*go, Vec2(0, 0)));
	AddObject(go, "GUI");

	//prateleira_full
	go = new GameObject();
	go->AddComponentAsFirst(new Sprite(*go, "assets/img/objects/prateleira_full.png"));
	go->box.SetPos(Vec2(0, 32));
	AddObject(go, "MAIN");
	std::string path;
	int pos = 220;
	for (int i = 0; i <= 4; i++) {
		path = "prateleira" + std::to_string((rand() % 13));
		//prateleira
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, path, 1, Vec2(1, 1), true, false));
		go->box.SetPos(Vec2(78, pos));
		AddObject(go, "MAIN");
		pos += 124;

	}
	pos = 220;
	for (int i = 0; i <= 4; i++) {
		path = "prateleira" + std::to_string((rand() % 13));
		//prateleira
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, path, 1, Vec2(1, 1), true, false));
		go->box.SetPos(Vec2(232, pos));
		AddObject(go, "MAIN");
		pos += 124;

	}

	pos = 220;
	for (int i = 0; i <= 4; i++) {
		path = "prateleira" + std::to_string((rand() % 13));
		//prateleira
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, path, 1, Vec2(1, 1), true, false));
		go->box.SetPos(Vec2(780, pos));
		AddObject(go, "MAIN");
		pos += 124;

	}

	pos = 220;
	for (int i = 0; i <= 4; i++) {
		path = "prateleira" + std::to_string((rand() % 13));
		//prateleira
		go = new GameObject();
		go->AddComponentAsFirst(new MainObject(*go, path, 1, Vec2(1, 1), true, false));
		go->box.SetPos(Vec2(936, pos));
		AddObject(go, "MAIN");
		pos += 124;

	}

	// Thrashcan
	go = new GameObject();
	go->AddComponentAsFirst(new MainObject(*go, "trashcan", 1, Vec2(3, 3), true, true));
	go->box.SetCenter((mw / 2) - 180, (mh / 2) + 160);
	AddObject(go, "MAIN");

	/*// TODO Reception
	go = new GameObject();
	go->AddComponentAsFirst(new MainObject(*go, "bench", 1, Vec2(3, 3), true, true));
	go->box.SetCenter((mw / 2), (mh / 2) - 100);
	AddObject(go, "MAIN");*/

	//NPCs
	go = new GameObject();
	go->box.SetCenter((mw / 2) - 500, (mh / 2) - 110);
	go->AddComponentAsFirst(new NPCTutorial(*go, NPCList[rand() % NPCList.size()]));
	AddObject(go, "MAIN");
	GameData::nCivilians++;

	go = new GameObject();
	go->box.SetCenter((mw / 2) - 480, (mh / 2) - 50);
	go->AddComponentAsFirst(new NPCTutorial(*go, NPCList[rand() % NPCList.size()]));
	AddObject(go, "MAIN");
	GameData::nCivilians++;

	go = new GameObject();
	go->box.SetCenter((mw / 2) + 200, (mh / 2) + 100);
	go->AddComponentAsFirst(new NPCTutorial(*go, Personality("girl", 150, 200, 1, 3, 1, 3, { "hobo" }, { "suit", "tree" })));
	AddObject(go, "MAIN");
	GameData::nCivilians++;

	go = new GameObject();
	go->box.SetCenter((mw / 2) + 300, (mh / 2) - 100);
	go->AddComponentAsFirst(new NPCTutorial(*go, NPCList[rand() % NPCList.size()]));
	AddObject(go, "MAIN");
	GameData::nCivilians++;

	go = new GameObject();
	go->box.SetCenter((mw / 2) + 500, (mh / 2) + 150);
	go->AddComponentAsFirst(new NPCTutorial(*go, NPCList[rand() % NPCList.size()]));
	AddObject(go, "MAIN");
	GameData::nCivilians++;

	//Monsters
	goLastMonster = new GameObject();
	goLastMonster->box.SetCenter((mw / 2) - 450, (mh / 2) + 170);
	goLastMonster->AddComponentAsFirst(new MonsterTutorial(*goLastMonster, monsterList[rand() % monsterList.size()]));
	AddObject(goLastMonster, "MAIN");
	GameData::nMonsters++; 
	GameData::nMaxMonsters++;

	goSecondMonster = new GameObject();
	goSecondMonster->box.SetCenter((mw / 2) - 10, (mh / 2) - 30);
	goSecondMonster->AddComponentAsFirst(new MonsterTutorial(*goSecondMonster, Personality("suit", 100, 150, 5, 0.3, 2, 2, { "bench", "girl" }, { "thrashcan" })));
	AddObject(goSecondMonster, "MAIN");
	GameData::nMonsters++;
	GameData::nMaxMonsters++;

	// Librarian
	goBlib = new GameObject();
	goBlib->box.SetCenter((mw / 2), (mh / 2) - 170);
	goBlib->AddComponentAsFirst(new MonsterTutorial(*goBlib, Personality("blib", 300, 250, 1, 2, 2, 2, {}, {})));
	AddObject(goBlib, "MAIN");
	GameData::nMonsters++;
	GameData::nMaxMonsters++;

	//Players
	go = new GameObject();
	go->AddComponentAsFirst(new Player(*go, "lucas", 1));
	go->box.SetCenter((mw / 2), (mh / 2) + 200);
	AddObject(go, "MAIN");

	Camera::Follow(go);

	backgroundMusic = Music("assets/audio/theme.ogg");
	backgroundMusic.Play();
}

TutorialStageState::~TutorialStageState() {
	GameData::mapSize = Vec2();
	GameData::nMonsters = 0;
	GameData::nMaxMonsters = 0;
	GameData::nCivilians = 0;
	GameData::player = std::weak_ptr<GameObject>();
	delete set;
}

void TutorialStageState::LoadAssets() {

}

void TutorialStageState::Start() {
	LoadAssets();
	StartArray();
	started = true;
}

void TutorialStageState::Pause() {
	for (int i = objects["MAIN"].size() - 1; i >= 0; i--) {
		if (objects["MAIN"][i]->GetComponent("NPC") && !objects["MAIN"][i]->GetComponent("Boss")) {
			if (Camera::GetFocus() == objects["MAIN"][i].get()) {}
			//Camera::Unfollow();
			//objects["MAIN"].erase(objects["MAIN"].begin() + i);
		}
	}
}

void TutorialStageState::Resume() {

}

void TutorialStageState::CollisionCheck() {
	for (unsigned i = 0; i < objects["MAIN"].size(); i++) {
		for (unsigned j = i + 1; j < objects["MAIN"].size(); j++) {
			if (objects["MAIN"][i]->IsActive() && objects["MAIN"][j]->IsActive()) {
				Collider* objA = (Collider*)objects["MAIN"][i]->GetComponent("Collider");
				Collider* objB = (Collider*)objects["MAIN"][j]->GetComponent("Collider");
				if (objA && objB) {
					bool collided = false;
					if (objA->GetMode() == Collider::RECT) {
						if (objB->GetMode() == Collider::RECT)
							collided = Collision::IsCollidingRectRect(objA->box, objB->box, objA->rotation, objB->rotation);
						else
							collided = Collision::IsCollidingCircleRect(objB->circle, objA->box, objA->rotation);
					}
					else {
						if (objB->GetMode() == Collider::RECT)
							collided = Collision::IsCollidingCircleRect(objA->circle, objB->box, objB->rotation);
						else
							collided = Collision::IsCollidingCircleCircle(objA->circle, objB->circle);
					}
					if (collided) {
						objects["MAIN"][i]->NotifyCollision(*objects["MAIN"][j]);
						objects["MAIN"][j]->NotifyCollision(*objects["MAIN"][i]);
					}
				}
			}
		}
	}
}

void TutorialStageState::DeletionCheck() {
	for (auto& i : objects) {
		for (int j = i.second.size() - 1; j >= 0; j--) {
			if (i.second[j]->IsDead()) {
				if (Camera::GetFocus() == i.second[j].get())
					Camera::Unfollow();

				if (i.second[j]->GetComponent("Soul")) {
					GameData::nMonsters--;
					GameData::eventT.Restart();
				}
				else if (i.second[j]->GetComponent("NPCTutorial") && !i.second[j]->GetComponent("MonsterTutorial")) {
					GameData::nCivilians--;
				}
				i.second.erase(i.second.begin() + j);
			}
		}
	}
}

void TutorialStageState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY)) {
		Game::GetInstance().Push(new PauseState());
	}

	if(InputManager::KeyPress(SDLK_F1))
		GameData::debug = !GameData::debug;

	if(InputManager::KeyPress(SDLK_F2))
		GameData::paused = !GameData::paused;

	if (hudChecked == false) {
		for (unsigned i = 0; i < objects["GUI"].size(); i++) {
			objects["GUI"][i]->Deactivate();
		}
		hudChecked = true;
	}

	if (GameData::nMonsters == 0) {
		gameOver = true;
		GameData::playerVictory = true;
	}
	else if(GameData::player.expired()) {
		gameOver = true;
		GameData::playerVictory = false;
	}

	if (!gameOver) {
		if (!GameData::paused) {
			GameData::eventT.Update(dt);
		}
		switch (tutorialScene) {
		 case 0:
				LibrarianTutorialUpdate(dt);
				break;
			case 1:
				SecondMonsterTutorialUpdate(dt);
				break;
			case 2:
				FreeTutorialUpdate(dt);
				break;
		}
	}
	else {
		Game::GetInstance().Push(new EndState());
	}

	std::sort(objects["EFFECT"].begin(), objects["EFFECT"].end(), SortRenderOrderTutorial_MS);
	std::sort(objects["MAIN"].begin(), objects["MAIN"].end(), SortRenderOrderTutorial_MS);
}

void TutorialStageState::LibrarianTutorialUpdate(float dt) {
	if(!startDialog){
		goDialog = new GameObject();
		goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Então é isso, você encontra um livro falante bonito e simpático como eu e simplesmente   decide deixá-lo na biblioteca mais próxima.", Vec2(512, 500)));
		AddObject(goDialog, "DIALOG");
		startDialog = true;
	}

	if (InputManager::KeyPress(CONFIRM)) {
		dialogScene += 1;
		std::string key1 = SDL_GetKeyName(GameData::MAGIC_BUBBLES);
		std::string key2 = SDL_GetKeyName(GameData::MAGIC_FIREBALL);
		std::string key3 = SDL_GetKeyName(GameData::MAGIC_CAPTURE);
		switch (dialogScene) {
		case 1:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Pera aí! Tem algo errado nessa biblioteca, eu sinto mais um dos meus por aqui. Assim como eu me passo por um livro tem outros que se passam como um de vocês.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 2:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Então ... agora que eu te disse isso eu acho  que eles não vão deixar isso passar barato,  acho melhor você tomar a iniciativa antes que eles percebam que você sabe o segredo deles hehehehehe", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 3:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Acho melhor eu te explicar como funcionam as coisas então, vamos lá, eu vou ajudar você a combater esses monstros com a minha mágica.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 4:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf","A tecla: "+ key1 + " -> Atira uma chuva de bolhas mágicas para enfraquecer os monstros!" , Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 5:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "A tecla: " + key2 + " -> Atira uma poderosa magia que alcança uma distância maior e explode no final, sendo capaz de acertar vários dos monstros.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 6:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "A tecla: " + key3 + " -> Atira uma fita mágica capaz de prender os monstros quando eles estiverem atordoados, capturá-los é a única maneira que alguem como você vai conseguir vencê-los.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 7:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Com esse arsenal de habilidades dignas do mais digníssimo livro mágico eu tenho certeza que   até você deve conseguer se livrar desses monstros.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 8:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Eu vou te ajudar um pouco mais dessa vez, vou tentar revelar um dos monstros que estão por aqui, ele deve ficar atordoado com isso, aproveite a oportunidade para capturá-lo com a minha magia.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 9:
			goDialog->Deactivate();
			blibMonster = (MonsterTutorial *)goBlib->GetComponent("MonsterTutorial");
			blibMonster->Transform();
			blibMonster->SetMStunT(2147483646);
			break;
		}
	}
	if (dialogScene >= 9) {
		if (goBlib->IsDead()) {
			dialogScene = 0;
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Viu só, com a minha grande ajuda é bem fácil. Mas não acaba por aqui, como eu disse antes  eles vão tentar se disfarçar ao máximo para não serem percebidos e cabe a você descobrir esses disfarces.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			tutorialScene++;
		}
		else if (blibMonster->GetAction() != "mStun" && blibMonster->GetAction() != "mTransform") {
			blibMonster->SetAction("mStun");
		}
	}
	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	UpdateArray(dt, "DIALOG");
	CollisionCheck();
	DeletionCheck();
	

}

void TutorialStageState::SecondMonsterTutorialUpdate(float dt) {
	if (InputManager::KeyPress(CONFIRM)) {
		switch (dialogScene) {
		case 1:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Como descobrir o disfarce se são exatamente iguais a nós? Isso deve ser o que o vosso simples cérebro está pensando, pois bem, não é por sermos todos monstros que fará com que eles tenham um exímio intelecto como o meu.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 2:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Na verdade eles são tão ineptos no que tentam fazer que nem um simples disfarce conseguem fazer direito, se prestar bem atenção verá que eles possuem uma personalidade bem distante dá que se espera.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 3:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Se seu simples intelecto não conseguiu entender então eu vou te mostrar.Preste bem atenção naquele homem de terno, vamos ver como ele age.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 4:
			goDialog->Deactivate();
			suitMoves = true;
			blibMonster = (MonsterTutorial*)goSecondMonster->GetComponent("MonsterTutorial");
			suitDialog = true;
			break;
		case 5:
			goDialog->Deactivate();
			for (unsigned i = 0; i < objects["GUI"].size(); i++) {
				objects["GUI"][i]->Activate();
			}
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Eis que agora você deve conseguir enxergar os milagres que minhas informações trazem a você.Mas como eu não espero que seu intelecto seja capaz de entender eu vou explicar para você.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 6:
			goDialog->Deactivate();
			goSetas = new GameObject();
			setas = new Sprite(*goSetas, "assets/img/HUD/setaEsquerda.png");
			goSetas->AddComponent(setas);
			setas->SetScale(Vec2(4, 4));
			goSetas->AddComponent(new CameraFollower(*goSetas, Vec2(220, 24)));
			AddObject(goSetas, "GUI");
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Aqui vão estar informações que estarei acompanhando sobre você, os corações  representam sua saúde, se todos esvaziarem,   bem, meus pêsames.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 7:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Os simbolos mágicos abaixo do coração é a atual magia que eu estarei pronto para preparar,  dessa maneira até você pode acompanhar minhas  magias superiores.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 8:
			goSetas->Deactivate();
			goDialog->Deactivate();
			goSetas = new GameObject();
			setas = new Sprite(*goSetas, "assets/img/HUD/setaDireita.png");
			goSetas->AddComponent(setas);
			setas->SetScale(Vec2(4, 4));
			goSetas->AddComponent(new CameraFollower(*goSetas, Vec2(804, 20)));
			AddObject(goSetas, "GUI");
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Eu consigo sentir o quão desconfiado esses monstros se sentem, por meio do meu belo olho mágico eu consigo te mostrar o quão desconfiado o monstro está.Se perceber que você está procurando por ele,o monstro se transformará.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 9:
			goSetas->Deactivate();
			goDialog->Deactivate();
			goSetas = new GameObject();
			setas = new Sprite(*goSetas, "assets/img/HUD/setaDireita.png");
			goSetas->AddComponent(setas);
			setas->SetScale(Vec2(4, 4));
			goSetas->AddComponent(new CameraFollower(*goSetas, Vec2(750, 120)));
			AddObject(goSetas, "GUI");
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Eu consigo também te mostrar quantas pessoas e quantos monstros existem por perto, dessa maneira você consegue saber quantos monstros faltam para encontrar.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 10:
			goSetas->Deactivate();
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Agora que você tem minha ajuda as coisas   ficaram muito fáceis, vou deixar você capturar sozinho esse monstro disfarçado nesse homem de terno.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			dialogScene++;
			break;
		case 11:
			goDialog->Deactivate();
			dialogScene++;
			break;
		}

	}
	if (suitDialog) {
		if (suitMoves) {
			blibMonster->WalkToPoint(Vec2((GameData::mapSize.x / 2) - 180, (GameData::mapSize.y / 2) + 160), 2);
			suitMoves = false;
		}
		if (blibMonster->GetAction() == IDLE && suitDialog) {
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Viu só o que eu disse, quem por acaso teria  medo de uma lixeira, foi ridículo de minha  parte sequer compará-los a mim. Bem, acho que está na hora de lhe agraciar com mais um pouco  do meu conhecimento.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			suitDialog = false;
			dialogScene++;
		}
	}

	if (goSecondMonster->IsDead()) {
		dialogScene = 0;
		goDialog = new GameObject();
		goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Realmente minha magia é tão forte que até mesmo você conseguiu derrotar esse monstro.Vamos para o que interessa agora.", Vec2(512, 500)));
		AddObject(goDialog, "DIALOG");
		tutorialScene++;
	}

	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	UpdateArray(dt, "DIALOG");
	UpdateArray(dt, "GUI");
	CollisionCheck();
	DeletionCheck();

}

void TutorialStageState::FreeTutorialUpdate(float dt) {
	if (InputManager::KeyPress(CONFIRM)) {
		dialogScene += 1;
		switch (dialogScene) {
		case 1:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Esse tempo todo eu ainda estive te ajudando com uma magia muito poderosa que congelava o tempo, mas agora você estará por si para testar tudo o que aprendeu.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 2:
			goDialog->Deactivate();
			goDialog = new GameObject();
			goDialog->AddComponent(new DialogBox(*goDialog, "assets/img/HUD/dialogG.png", "assets/font/VT323.ttf", "Existe mais um monstro escondido, encontre ele  e capture-o para sairmos desta maldita prisão  de livros.", Vec2(512, 500)));
			AddObject(goDialog, "DIALOG");
			break;
		case 3:
			goDialog->Deactivate();
			for (unsigned i = 0; i < objects["MAIN"].size(); i++) {
				NPCTutorial* npc = static_cast<NPCTutorial*>(objects["MAIN"][i]->GetComponent("NPCTutorial"));
				if (npc && npc->GetTutorialControl()) {
					npc->ToggleTutorialControl();
				}
			}
			break;
		}
	}
	UpdateArray(dt, "BG");
	UpdateArray(dt, "EFFECT");
	UpdateArray(dt, "MAIN");
	UpdateArray(dt, "MISC");
	UpdateArray(dt, "DIALOG");
	UpdateArray(dt, "GUI");
	CollisionCheck();
	DeletionCheck();

}

void TutorialStageState::Render() {
	RenderArray("BG");
	RenderArray("EFFECT");
	RenderArray("MAIN");
	RenderArray("MISC");
	RenderArray("DIALOG");
	RenderArray("GUI");
}
