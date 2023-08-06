#include "Game.h"

void Game::init() {
  for (auto column : grid.tiles) {
    for (auto tile : column) {
      tile.reset();
    }
  }

  spawnTile();
}

void Game::spawnTile() {
  // randomize later
  uint8_t col = 0;
  uint8_t row = 0;

  grid.tiles.at(col).at(row).rankUp();
  MLOGD("TileGame", "Tile spawned at (%d, %d)", col, row);
}

Game::Game() {
  // test lightup
  init();
  MLOGI("TileGame", "Game started");
}
