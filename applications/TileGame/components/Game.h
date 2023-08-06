#pragma once

#include "TileGrid.h"

class Game {
  TileGrid grid;

  void init();

  void spawnTile();

 public:
  // constructor
  Game();
};