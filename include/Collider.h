#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "Component.h"

#include <string>

class Collider : public Component {
private:
	Vec2 scale;
	Vec2 offset;

public:
	Rect box;
	float rotation;

	Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
	~Collider();
	void SetScale(Vec2 scale);
	void SetOffset(Vec2 offset);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif /* COLLIDER_H_ */
