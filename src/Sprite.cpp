#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	width = 0;
	height = 0;
	scale = Vec2(1, 1);
	frameCount = 1;
	currentFrame = 0;
	frameTime = 1;
	timeElapsed = 0;
	loop = true;
}

Sprite::Sprite(GameObject& associated, std::string file, 
			   int frameCount, float frameTime, bool loop, 
			   float secondsToSelfDestruct) : Sprite(associated) {
	Sprite::frameCount = frameCount;
	Sprite::frameTime = frameTime;
	Sprite::loop = loop;
	Sprite::secondsToSelfDestruct = secondsToSelfDestruct;
	Open(file);
}

Sprite::~Sprite() {
	texture = nullptr;
}

void Sprite::Open(std::string file) {
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
	SetClip(0, 0, (width/frameCount), height);
	associated.box.w = GetWidth();
	associated.box.h = GetHeight();
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::SetScale(Vec2 scale) {
	Sprite::scale = scale;
	associated.box.w = GetWidth();
	associated.box.h = GetHeight();
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCount) {
	Sprite::frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime) {
	Sprite::frameTime = frameTime;
}

void Sprite::Update(float dt) {
	if(secondsToSelfDestruct > 0) {
		selfDestructCount.Update(dt);
		if(selfDestructCount.Get() > secondsToSelfDestruct)
			associated.RequestDelete();
	}
	if(frameCount > 1) {
		timeElapsed += dt;
		if(timeElapsed > frameTime) {
			timeElapsed -= frameTime; 
				if(currentFrame < frameCount-1)
					currentFrame++;
				else if(loop)
					currentFrame = 0;
				SetClip(currentFrame*(width/frameCount), 0, (width/frameCount), height);
		}
	}
}

void Sprite::Render() {
	Render(associated.box.x-Camera::pos.x, associated.box.y-Camera::pos.y);
}

void Sprite::Render(int x, int y) {
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = (int)clipRect.w*scale.x;
	dstRect.h = (int)clipRect.h*scale.y;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect,
					 associated.rotation, nullptr, SDL_FLIP_NONE);
}

bool Sprite::Is(std::string type) {
	return (type == "Sprite");
}

int Sprite::GetWidth() {
	return (int)(width/frameCount)*scale.x;
}

int Sprite::GetHeight() {
	return (int)height*scale.y;
}

Vec2 Sprite::GetScale() {
	return scale;
}

bool Sprite::IsOpen() {
	return (!texture) ? false : true;
}
