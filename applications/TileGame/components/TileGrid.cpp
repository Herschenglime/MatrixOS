#include <algorithm>

#include "TileGrid.h"

TileGrid::TileGrid() {

  tiles.reserve(4);

  MLOGD("TileGame", "Populating grid");
  for (uint8_t colNum = 0; colNum < 4; colNum++)
  {
    MLOGD("TileGame", "col %d", colNum);
    vector<Tile> column;
    column.reserve(4);

    for (uint8_t rowNum = 0; rowNum < 4; rowNum++)
    {
      MLOGD("TileGame", "row %d", rowNum);
      Point topLeft(2 * colNum, 2 * rowNum);
      Point topRight(2 * colNum + 1, 2 * rowNum);
      Point bottomLeft(2 * colNum, 2 * rowNum + 1);
      Point bottomRight(2 * colNum + 1, 2 * rowNum + 1);

      MLOGD("TileGame", "Points are (%d, %d), (%d, %d), (%d, %d), (%d, %d)", topLeft.x, topLeft.y, topRight.x, topRight.y, bottomLeft.x, bottomLeft.y, bottomRight.x,
            bottomRight.y);

      Tile newTile(topLeft, topRight, bottomLeft, bottomRight);
      newTile.col = colNum;
      newTile.row = rowNum;
      MLOGD("TileGame", "New tile created");

      column.push_back(newTile);
      MLOGD("TileGame", "Tile added to column");
    }

    tiles.push_back(column);
    MLOGD("TileGame", "Column added to grid");
  }
}

void TileGrid::removeFromEmpty(Tile& tile) {
  // remove spawned tile from empty list
  auto position = find(emptyTiles.begin(), emptyTiles.end(), &tile);
  if (position != emptyTiles.end())  // == grid.emptyTiles.end() means the element was not found
    emptyTiles.erase(position);

  MLOGD("TileGame", "Tile at (%d, %d) removed from empty list.", tile.col, tile.row);
}

void TileGrid::moveTile(Tile& original, Tile& newPos) {
  newPos.setRank(original.getRank());
  original.setRank(0);
  emptyTiles.push_back(&original);
}

void TileGrid::combineTiles(Tile& original, Tile& destination) {
  destination.rankUp();
  original.setRank(0);
  emptyTiles.push_back(&original);
  MLOGD("TileGame", "Tiles combined!");
}
