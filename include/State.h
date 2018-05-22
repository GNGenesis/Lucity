#ifndef STATE_H_
#define STATE_H_

#include "GameObject.h"

#include <vector>
#include <memory>

class State {
protected:
	void StartArray();
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	std::vector<std::shared_ptr<GameObject>> objectArray;
	bool popRequested;
	bool quitRequested;
	bool started;

public:
	State();
	virtual ~State();
	virtual std::weak_ptr<GameObject> AddObject(GameObject* go);
	virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
	virtual void LoadAssets() = 0;
	virtual void Start() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	bool PopRequested();
	bool QuitRequested();
};

#endif /* STATE_H_ */
