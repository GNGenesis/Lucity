#include "AOE.h"
#include "Game.h"
#include "Camera.h"

AOE::AOE(GameObject& associated, float scale) : Component(associated) {
	AOE::scale = scale;
}

AOE::~AOE() {

}

void AOE::SetScale(float scale) {
	AOE::scale = scale;
}


void AOE::Update(float dt) {
	circle.SetPos(associated.box.GetCenter());
	circle.SetRadius(associated.box.GetCenter().GetDS(Vec2(associated.box.x, associated.box.y + associated.box.h)) *scale);
	rotation = associated.rotation;
}

void AOE::Render() {
#ifdef DEBUG
	typedef int32_t s32;
	s32 x = circle.r - 1;
	s32 y = 0;
	s32 tx = 1;
	s32 ty = 1;
	s32 err = tx - ((s32)circle.r << 1); // shifting bits left by 1 effectively
		   							  // doubles the value. == tx - diameter
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x + x, (s32)circle.y - y);
		SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x + x, (s32)circle.y + y);
		SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x - x, (s32)circle.y - y);
		SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x - x, (s32)circle.y + y);
		SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x + y, (s32)circle.y - x);
		SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x + y, (s32)circle.y + x);
		SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x - y, (s32)circle.y - x);
		SDL_RenderDrawPoint(Game::GetInstance().GetRenderer(), (s32)circle.x - y, (s32)circle.y + x);

		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		else if (err > 0)
		{
			x--;
			tx += 2;
			err += tx - ((s32)circle.r << 1);
		}
	}
#endif // DEBUG
}

bool AOE::Is(std::string type) {
	return (type == "AOE");
}
