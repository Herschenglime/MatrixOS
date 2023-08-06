#pragma once

#include <vector>
#include "Tile.h"

  struct TileGrid {
    vector<vector<Tile>> tiles; //4 rows, 4 columns

    void lightTile(int col, int row);
    TileGrid();
  };
