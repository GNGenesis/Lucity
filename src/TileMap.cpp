#include "TileMap.h"
#include "Camera.h"

#include <fstream>

TileMap::TileMap(GameObject& associated, TileSet* tileSet, std::string file) : Component(associated) {
	TileMap::tileSet = tileSet;
	Load(file);
}

TileMap::~TileMap() {
	tileSet = nullptr;
	tileMatrix.clear();
}

void TileMap::Load(std::string file) {
	std::ifstream fileReader("assets/map/tileMap.txt", std::ios::in);
	if(fileReader.good()) {
		int x;
		char s;
		fileReader >> mapWidth >> s >> mapHeight >> s >> mapDepth >> s;
		for(int k = 0; k < mapDepth; k++) {
			for(int j = 0; j < mapHeight; j++) {
				for(int i = 0; i < mapWidth; i++) {
					fileReader >> x >> s;
					tileMatrix.emplace_back(x-1);
				}
			}
		}
	}else{
		printf("Unable to read %s", file.c_str());
	}
	fileReader.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
	TileMap::tileSet = tileSet;
}

void TileMap::Update(float dt) {
	
}

void TileMap::Render() {
	for(int i = 0; i < mapDepth; i++) {
		RenderLayer(i, Camera::pos.x*(1 + i*0.5), Camera::pos.y*(1 + i*0.5));
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	for(int j = 0; j < mapHeight; j++) {
		for(int i = 0; i < mapWidth; i++) {
			int x = i*tileSet->GetTileWidth()-cameraX;
			int y = j*tileSet->GetTileHeight()-cameraY;
			tileSet->RenderTile(At(i, j, layer), x, y);
		}
	}
}

bool TileMap::Is(std::string type) {
	return (type == "TileMap");
}

int TileMap::At(int x, int y, int z) {
	return tileMatrix[(x)+(y*mapWidth)+(z*mapWidth*mapHeight)];
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}
