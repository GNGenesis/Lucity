#ifndef HUD_H_
#define HUD_H_

#include "Component.h"
#include "Timer.h"

#include <string>
#include <vector>
#include <memory>

class HUD : public Component {
private:
	std::weak_ptr<GameObject> player_info;

	std::vector<std::weak_ptr<GameObject>> health;
	int healthTrack;

	std::vector<std::weak_ptr<GameObject>> attack;

	std::vector<std::weak_ptr<GameObject>> timer;

	std::weak_ptr<GameObject> npcs;
	std::weak_ptr<GameObject> npcsTXT;

	std::weak_ptr<GameObject> monsters;
	std::weak_ptr<GameObject> monstersTXT;

public:
	HUD(GameObject& associated);
	~HUD();
	void Start();
	void Update(float dt);
	bool Is(std::string type);
};

#endif /* HUD_H_ */