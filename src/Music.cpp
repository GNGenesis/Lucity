#include "Music.h"
#include "Resources.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file) : Music() {
	Open(file);
}

Music::~Music() {
	if(IsPlaying())
		Stop(0);
	music = nullptr;
}

void Music::Open(std::string file) {
	music = Resources::GetMusic(file);
}

void Music::Play(int times) {
	if(Mix_PlayMusic(music.get(), times) == -1) {
		printf("Mix_PlayedMusic failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void Music::Stop(int msToStop) {
	if(!Mix_FadeOutMusic(msToStop)) {
		printf("Mix_FadeOutMusic failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

bool Music::IsOpen() {
	return (!music) ? false : true;
}

bool Music::IsPlaying() {
	return (Mix_PlayingMusic());
}
