#ifndef TILESET_H_
#define TILESET_H_

#include "Sprite.h"

#include <string>

class TileSet {
private:
	Sprite tileSet;
	int tileWidth;
	int tileHeight;
	int rows;
	int columns;

public:
	TileSet(GameObject& associated, std::string file, int tileWidth, int tileHeight);
	~TileSet();
	void RenderTile(int index, int x, int y);
	int GetTileWidth();
	int GetTileHeight();
};

#endif /* TILESET_H_ */
