#ifndef MISCOBJECT_H_
#define MISCOBJECT_H_

#include "Component.h"
#include "Timer.h"

#include <string>
#include <vector>
#include <memory>

class MiscObject : public Component {
private:
	std::weak_ptr<GameObject> mainObject;

public:
	MiscObject(GameObject& associated, GameObject& mainObject,std::string miscNome,Vec2 scale);
	~MiscObject();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif
