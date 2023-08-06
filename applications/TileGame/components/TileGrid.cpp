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

      MLOGD("TileGame", "Points are (%d, %d), (%d, %d), (%d, %d), (%d, %d)", 
      topLeft.x, topLeft.y,
      topRight.x, topRight.y,
      bottomLeft.x, bottomLeft.y,
      bottomRight.x, bottomRight.y
      );
     
      Tile newTile(topLeft, topRight, bottomLeft, bottomRight);
      MLOGD("TileGame", "New tile created");

      column.push_back(newTile);
      MLOGD("TileGame", "Tile added to column");
    }

    tiles.push_back(column);
    MLOGD("TileGame", "Column added to grid");
  }
}

//should light up all 4 points within the tile
void TileGrid::lightTile(int col, int row) {
  Tile tileToLight = tiles.at(col).at(row);
  for (Point point : tileToLight.subPoints) {
      MatrixOS::LED::SetColor(point, 0x0000FF, 0); 
  }
}