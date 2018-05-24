#ifndef STATE_H_
#define STATE_H_

#include "GameObject.h"

#include <vector>
#include <unordered_map>
#include <memory>

class State {
protected:
	void StartArray();
	virtual void UpdateArray(float dt, std::string layer);
	virtual void RenderArray(std::string layer);

	std::unordered_map<std::string, std::vector<std::shared_ptr<GameObject>>> objects;
	bool popRequested;
	bool quitRequested;
	bool started;

public:
	State();
	virtual ~State();
	virtual std::weak_ptr<GameObject> AddObject(GameObject* go, std::string layer);
	virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go, std::string layer);
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
