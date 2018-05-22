#include "Collider.h"
#include "Game.h"
#include "Camera.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
	Collider::scale = scale;
	Collider::offset = offset;
}

Collider::~Collider() {

}

void Collider::SetScale(Vec2 scale) {
	Collider::scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
	Collider::offset = offset;
}

void Collider::Update(float dt) {
	box.SetSize(associated.box.GetSize()*scale);
	box.SetCenter(associated.box.GetCenter()+offset);
	rotation = associated.rotation;
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center(box.GetCenter());
	SDL_Point points[5];

	Vec2 point;
	point = (Vec2(box.x, box.y)-center).Rotate(rotation)+center-Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x+box.w, box.y)-center).Rotate(rotation)+center-Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x+box.w, box.y+box.h)-center).Rotate(rotation)+center-Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y+box.h)-center).Rotate(rotation)+center-Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type) {
	return (type == "Collider");
}
