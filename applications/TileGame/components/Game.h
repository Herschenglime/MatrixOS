#pragma once

#include "Tile.h"
#include "TileGrid.h"

class Game {
  TileGrid grid;


  void spawnTile();

 public:
  // constructor
  Game();

  void init();
  bool moveRight();
};