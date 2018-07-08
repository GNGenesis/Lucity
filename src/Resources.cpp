#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
	if(!imageTable.count(file)) {
		SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		imageTable.emplace(file, std::shared_ptr<SDL_Texture>(texture, [](SDL_Texture* p) { SDL_DestroyTexture(p); }));
	}
	if(!imageTable.at(file)) {
		printf("IMG_LoadTexture failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return imageTable.at(file);
}

void Resources::ClearImages() {
	for(auto& i: imageTable)
		if(i.second.unique()) {
			printf("Deleting: ");
			printf(i.first.c_str());
			imageTable.erase(i.first);
			printf(" - done\n");
		}
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
	if(!musicTable.count(file)) {
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		musicTable.emplace(file, std::shared_ptr<Mix_Music>(music, [](Mix_Music* p) { Mix_FreeMusic(p); }));
	}
	if(musicTable.at(file) == nullptr) {
		printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return musicTable.at(file);
}

void Resources::ClearMusics() {
	for(auto& i: musicTable)
		if(i.second.unique()) {	
			printf("Deleting: ");
			printf(i.first.c_str());
			musicTable.erase(i.first);
			printf(" - done\n");
		}
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
	if(!soundTable.count(file)) {
		Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
		soundTable.emplace(file, std::shared_ptr<Mix_Chunk>(chunk, [](Mix_Chunk* p) { Mix_FreeChunk(p); }));
	}
	if(soundTable.at(file) == nullptr) {
		printf("Mix_LoadWAV failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return soundTable.at(file);
}

void Resources::ClearSounds() {
	for(auto& i: soundTable)
		if(i.second.unique()) {	
			printf("Deleting: ");
			printf(i.first.c_str());
			soundTable.erase(i.first);
			printf(" - done\n");
		}
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string fontFile, int fontSize) {
	char size[3];
	sprintf(size, "%d", fontSize);
	std::string key = fontFile+size;
	if(!fontTable.count(key)) {
		TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
		fontTable.emplace(key, std::shared_ptr<TTF_Font>(font, [](TTF_Font* p) { TTF_CloseFont(p); }));
	}
	if(fontTable.at(key) == nullptr) {
		printf("TTF_OpenFont failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return fontTable.at(key);
}

void Resources::ClearFonts() {
	for(auto& i: fontTable)
		if(i.second.unique()) {	
			printf("Deleting: ");
			printf(i.first.c_str());
			fontTable.erase(i.first);
			printf(" - done\n");
		}
}

void Resources::Clear() {
	//ClearFonts();
	//ClearSounds();
	//ClearMusics();
	//ClearImages();
}

void Resources::CleanUp() {
/*#ifdef DEBUG
	for(auto& i: fontTable) {
		printf("Deleting: ");
		printf(i.first.c_str());
		fontTable.erase(i.first);
		printf(" - done\n");
	}
	for(auto& i: soundTable) {
		printf("Deleting: ");
		printf(i.first.c_str());
		soundTable.erase(i.first);
		printf(" - done\n");
	}
	for(auto& i: musicTable) {
		printf("Deleting: ");
		printf(i.first.c_str());
		musicTable.erase(i.first);
		printf(" - done\n");
	}
	for(auto& i: imageTable) {
		printf("Deleting: ");
		printf(i.first.c_str());
		imageTable.erase(i.first);
		printf(" - done\n");
	}
#else*/
	fontTable.clear();
	soundTable.clear();
	musicTable.clear();
	imageTable.clear();
//#endif // DEBUG
}
