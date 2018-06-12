#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "Component.h"
#include "Rect.h"
#include "Circle.h"

#include <string>

class Collider : public Component {
public:
	enum ColliderMode { RECT, CIRCLE };

private:
	ColliderMode mode;
	Vec2 scale;
	Vec2 offset;
	int radius;

public:
	Rect box;
	float rotation;
	Circle circle;

	Collider(GameObject& associated, int radius);
	Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
	~Collider();
	void SetScale(Vec2 scale);
	void SetOffset(Vec2 offset);
	void SetRadius(int radius);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	int GetMode();
};

#endif /* COLLIDER_H_ */
