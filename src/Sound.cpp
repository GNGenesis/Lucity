#include "Sound.h"
#include "Resources.h"

Sound::Sound(GameObject& associated) : Component(associated) {
	chunk = nullptr;
	channel = -1;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated) {
	Open(file);
}

Sound::~Sound() {
	Stop();
	chunk = nullptr;
}

void Sound::Open(std::string file) {
	chunk = Resources::GetSound(file);
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(channel, chunk.get(), times-1);
	if(channel == -1) {
		printf("Mix_PlayChannel failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void Sound::Stop() {
	if(IsPlaying())
		Mix_HaltChannel(channel);
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(std::string type) {
	return (type == "Sound");
}

bool Sound::IsOpen() {
	return (!chunk) ? false : true;
}

bool Sound::IsPlaying() {
	return (Mix_Playing(channel));
}
