#ifndef MISCOBJECT_H_
#define MISCOBJECT_H_

#include "Component.h"

#include <string>
#include <memory>

class MiscObject : public Component {
private:
	std::weak_ptr<GameObject> mainObject;

public:
	MiscObject(GameObject& associated, GameObject& mainObject, std::string miscName, Vec2 scale);
	~MiscObject();
	void Update(float dt);
	bool Is(std::string type);
};

#endif /* MISCOBJECT_H_ */
