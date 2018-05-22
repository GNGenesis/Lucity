#include "TileSet.h"

TileSet::TileSet(GameObject& associated, std::string file, int tileWidth, int tileHeight) : tileSet(associated, file) {
	TileSet::tileWidth = tileWidth;
	TileSet::tileHeight = tileHeight;
	rows = tileSet.GetHeight()/tileHeight;
	columns = tileSet.GetWidth()/tileWidth;
}

TileSet::~TileSet() {

}

void TileSet::RenderTile(int index, int x, int y) {
	if(index > -1 && index < rows*columns) {
		int clipX = tileWidth*(index%columns);
		int clipY = tileHeight*(index/columns);
		tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
		tileSet.Render(x, y);
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}
