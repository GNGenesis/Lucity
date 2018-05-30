#ifndef AOE_H_
#define AOE_H_

#include "Component.h"

#include <string>

class AOE : public Component {
private:
	float scale;
	//Vec2 offset;

public:
	Circle circle;
	float rotation;

	//AOE(GameObject& associated, Vec2 scale = { 1, 1 }, Vec2 offset = { 0, 0 });
	AOE(GameObject& associated, float scale = 1);
	~AOE();
	void SetScale(float scale);
	//void SetOffset(Vec2 offset);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif /* COLLIDER_H_ */
