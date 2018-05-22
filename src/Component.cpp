#include "Component.h"

Component::Component(GameObject& associated) : associated(associated) {
	active = true;
}

Component::~Component() {

}

void Component::Start() {

}

void Component::NotifyCollision(GameObject& other) {

}

void Component::Activate() {
	active = true;
}

void Component::Deactivate() {
	active = false;
}

bool Component::IsActive() {
	return active;
}
