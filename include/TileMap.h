#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "Component.h"
#include "TileSet.h"

#include <string>
#include <vector>

class TileMap : public Component {
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;

public:
	TileMap(GameObject& associated, TileSet* tileSet, std::string file);
	~TileMap();
	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	void Update(float dt);
	void Render();
	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
	bool Is(std::string type);
	int At(int x, int y, int z = 0);
	int GetWidth();
	int GetHeight();
	int GetDepth();
};

#endif /* TILEMAP_H_ */
