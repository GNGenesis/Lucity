#include "State.h"

State::State() {
	popRequested = false;
	quitRequested = false;
	started = false;
}

State::~State() {
	for(auto& i: objects)
		i.second.clear();
	objects.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go, std::string layer) {
	std::shared_ptr<GameObject> shared = std::shared_ptr<GameObject>(go);
	objects[layer].emplace_back(shared);
	if(started)
		shared->Start();
	return shared;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go, std::string layer) {
	for(unsigned i = 0; i < objects[layer].size(); i++)
		if(objects[layer][i].get() == go)
			return objects[layer][i];
	return std::weak_ptr<GameObject>();
}

void State::StartArray() {
	for(auto& i: objects)
		for(unsigned j = 0; j < i.second.size(); j++)
			i.second[j]->Start();
}

void State::UpdateArray(float dt, std::string layer) {
	for(unsigned i = 0; i < objects[layer].size(); i++)
		objects[layer][i]->Update(dt);
}

void State::RenderArray(std::string layer) {
	for(unsigned i = 0; i < objects[layer].size(); i++)
		objects[layer][i]->Render();
}

bool State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}
