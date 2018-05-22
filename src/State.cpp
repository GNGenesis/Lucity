#include "State.h"

State::State() {
	popRequested = false;
	quitRequested = false;
	started = false;
}

State::~State() {
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	std::shared_ptr<GameObject> shared = std::shared_ptr<GameObject>(go);
	objectArray.emplace_back(shared);
	if(started)
		shared->Start();
	return shared;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	for(unsigned i = 0; i < objectArray.size(); i++)
		if(objectArray[i].get() == go)
			return objectArray[i];
	return std::weak_ptr<GameObject>();
}

void State::StartArray() {
	for(unsigned i = 0; i < objectArray.size(); i++)
		objectArray[i]->Start();
}

void State::UpdateArray(float dt) {
	for(unsigned i = 0; i < objectArray.size(); i++)
		objectArray[i]->Update(dt);
}

void State::RenderArray() {
	for(unsigned i = 0; i < objectArray.size(); i++)
		objectArray[i]->Render();
}

bool State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}
