#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"

class Camera {
private:
	static	GameObject* focus;

public:
	static Vec2 pos;
	static Vec2 speed;

	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
	static GameObject* GetFocus();
};

#endif /* CAMERA_H_ */
