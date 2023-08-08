#pragma once

#include "Tile.h"
#include "TileGrid.h"

class Game {
  TileGrid grid;


  void spawnTileAt(uint8_t col, uint8_t row);
  void spawnTileAt(Tile& tile);

 public:
  // constructor
  Game();

  void init();
  void init(bool debug);
  bool moveRight();
  bool moveLeft();
  bool moveDown();
  bool moveUp();
  void spawnTile();
};