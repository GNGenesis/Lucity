#ifndef SPRITE_H_
#define SPRITE_H_

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"
#include "Timer.h"

#include <string>
#include <memory>

class Sprite : public Component {
private:
	std::shared_ptr<SDL_Texture> texture;
	SDL_Rect clipRect;
	int width;
	int height;
	Vec2 scale;
	int frameCount;
	int currentFrame;
	float frameTime;
	float timeElapsed;
	bool loop;
	Timer selfDestructCount;
	float secondsToSelfDestruct;

public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, std::string file, 
		   int frameCount = 1, float frameTime = 1, bool loop = true, 
		   float secondsToSelfDesctruct = 0);
	~Sprite();
	void Open(std::string file);
	void SetClip(int x, int y, int w, int h);
	void SetScale(Vec2 scale);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	void Update(float dt);
	void Render();
	void Render(int x, int y);
	bool Is(std::string type);
	int GetWidth();
	int GetHeight();
	Vec2 GetScale();
	bool IsOpen();
};

#endif /* SPRITE_H_ */
