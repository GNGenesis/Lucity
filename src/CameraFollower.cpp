#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& associated, Vec2 truePos) : Component(associated) {
	CameraFollower::truePos = truePos;
}

CameraFollower::~CameraFollower() {
	
}

void CameraFollower::SetTruePos(Vec2 pos) {
	truePos = pos;
}

void CameraFollower::Update(float dt) {
	associated.box.SetPos(truePos+Camera::pos);
}

void CameraFollower::Render() {
	
}

bool CameraFollower::Is(std::string type) {
	return (type == "CameraFollower");
}