#ifndef SOUND_H_
#define SOUND_H_

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"

#include <string>
#include <memory>

class Sound : public Component {
private:
	std::shared_ptr<Mix_Chunk> chunk;
	int channel;

public:
	Sound(GameObject& associated);
	Sound(GameObject& associated, std::string file);
	~Sound();
	void Open(std::string file);
	void Play(int times = 1);
	void Stop();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	bool IsOpen();
	bool IsPlaying();
};

#endif /* SOUND_H_ */
