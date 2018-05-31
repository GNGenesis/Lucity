#include "Collider.h"
#include "Game.h"
#include "Camera.h"

Collider::Collider(GameObject& associated, int radius) : Component(associated) {
	Collider::mode = CIRCLE;
	Collider::radius = radius;
	box.SetSize(Vec2());
	circle.SetRadius(0);
}

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
	Collider::mode = RECT;
	Collider::scale = scale;
	Collider::offset = offset;
	box.SetSize(Vec2());
	circle.SetRadius(0);
}

Collider::~Collider() {

}

void Collider::SetScale(Vec2 scale) {
	Collider::scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
	Collider::offset = offset;
}

void Collider::SetRadius(int radius) {
	Collider::radius = radius;
}

void Collider::Update(float dt) {
	if(mode == RECT) {
		box.SetSize(associated.box.GetSize()*scale);
		box.SetCenter(associated.box.GetCenter()+offset);
		rotation = associated.rotation;
	}
	else if(mode == CIRCLE) {
		circle.SetRadius(radius);
		circle.SetCenter(associated.box.GetCenter()+offset);
	}
}

void Collider::Render() {
#ifdef DEBUG
	if(mode == RECT) {
		Vec2 center(box.GetCenter());
		SDL_Point points[5];

		Vec2 point;
		point = (Vec2(box.x-1, box.y-1)-center).Rotate(rotation)+center-Camera::pos;
		points[0] = {(int)point.x, (int)point.y};
		points[4] = {(int)point.x, (int)point.y};
		
		point = (Vec2(box.x+box.w, box.y-1)-center).Rotate(rotation)+center-Camera::pos;
		points[1] = {(int)point.x, (int)point.y};
		
		point = (Vec2(box.x+box.w, box.y+box.h)-center).Rotate(rotation)+center-Camera::pos;
		points[2] = {(int)point.x, (int)point.y};
		
		point = (Vec2(box.x-1, box.y+box.h)-center).Rotate(rotation)+center-Camera::pos;
		points[3] = {(int)point.x, (int)point.y};

		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
	}
	else if(mode == CIRCLE) {
		typedef int32_t s32;
		s32 x = circle.r - 1;
		s32 y = 0;
		s32 tx = 1;
		s32 ty = 1;
		s32 err = tx - ((s32)circle.r << 1); // shifting bits left by 1 effectively
			   							  // doubles the value. == tx - diameter
		while (x >= y) {
			//  Each of the following renders an octant of the circle
			SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x + x - Camera::pos.x, (s32)circle.y - y - Camera::pos.y);
			SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x + x - Camera::pos.x, (s32)circle.y + y - Camera::pos.y);
			SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x - x - Camera::pos.x, (s32)circle.y - y - Camera::pos.y);
			SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x - x - Camera::pos.x, (s32)circle.y + y - Camera::pos.y);
			SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x + y - Camera::pos.x, (s32)circle.y - x - Camera::pos.y);
			SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x + y - Camera::pos.x, (s32)circle.y + x - Camera::pos.y);
			SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x - y - Camera::pos.x, (s32)circle.y - x - Camera::pos.y);
			SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x - y - Camera::pos.x, (s32)circle.y + x - Camera::pos.y);

			if (err <= 0) {
				y++;
				err += ty;
				ty += 2;
			}
			else if (err > 0) {
				x--;
				tx += 2;
				err += tx - ((s32)circle.r << 1);
			}
		}
	}
#endif // DEBUG
}

bool Collider::Is(std::string type) {
	return (type == "Collider");
}

int Collider::GetMode() {
	return mode;
}
