#pragma once

#include <vector>
#include "Tile.h"

struct TileGrid {
  vector<vector<Tile>> tiles;  // 4 rows, 4 columns

  // constructor
  TileGrid();

  void moveTile(Tile& originalPos, Tile& newPos) {
    newPos.setRank(originalPos.getRank());
    originalPos.setRank(0);
  }
};
