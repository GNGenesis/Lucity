#ifndef CAMERAFOLLOWER_H_
#define CAMERAFOLLOWER_H_

#include "Component.h"

#include <string>

class CameraFollower : public Component {
public:
	Vec2 truePos;

	CameraFollower(GameObject& associated, Vec2 truePos = Vec2());
	~CameraFollower();
	void SetTruePos(Vec2 pos);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif /* CAMERAFOLLOWER_H_ */