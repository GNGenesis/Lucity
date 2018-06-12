#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Component.h"
#include "Character.h"
#include "Sprite.h"

#include <string>
#include <unordered_map>
#include <memory>

class Animator : public Component {
private:
	Character* character;
	Component* activeSprite;
	std::string name;
	std::unordered_map<std::string, Sprite*> sprites;

public:
	Animator(GameObject& associated, Character* character, std::string name);
	~Animator();
	void Start();
	void BuildSprites();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif /* ANIMATOR_H_ */