#include "Game.h"

void Game::init() {
  init(false);
}

void Game::init(bool debug) {
  for (auto column : grid.tiles)
  {
    for (auto tile : column)
    {
      tile.reset();
    }
  }

  if (debug)
  {
    MLOGI("TileGame", "Game in debug mode");
    spawnTileAt(0, 0);
    spawnTileAt(1, 1);
    spawnTileAt(2, 2);
    spawnTileAt(3, 3);
  }
  else
  {
    spawnTile();
  }

  MLOGD("TileGame", "Game initiated");
}

bool Game::moveRight() {
  // move each tile from right to left in each column
  for (int8_t colNum = 3; colNum >= 0; colNum--)
  {
    auto& column = grid.tiles.at(colNum);

    for (uint8_t rowNum = 0; rowNum < 4; rowNum++)
    {
      Tile& origTile = column.at(rowNum);
      MLOGD("TileGame", "Original tile is at (%d, %d) and has rank %d", colNum, rowNum, origTile.getRank());

      //   only move tile if there's something there (i.e. has rank)
      if (origTile.getRank() > 0)
      {
        // only tiles not on the right edge can move
        uint8_t nextCol = colNum + 1;

        if (nextCol < 4)
        {
          Tile* nextTilePtr = &grid.tiles.at(nextCol).at(rowNum);
          MLOGD("TileGame", "Next tile is at (%d, %d) and has rank %d", nextCol, rowNum, nextTilePtr->getRank());

          // check rank of tile to the right
          // if 0, look for the next one (keeping in mind boundaries of grid)
          while (nextTilePtr->getRank() == 0 && nextCol < 3)
          {
            nextTilePtr = &grid.tiles.at(++nextCol).at(rowNum);
            MLOGD("TileGame", "Col of nextTile is %d", nextCol);
          }

          auto& nextTile = *nextTilePtr;
          MLOGD("TileGame", "Tile for comparison is at (%d, %d) and has rank %d", nextCol, rowNum, nextTile.getRank());
          // if not on the right edge, compare current tile
          if (nextCol < 4)
          {
            if (origTile.getRank() == nextTile.getRank())
            {
              // do combination, implement later
              MLOGD("TileGame", "Tiles combined!");
            }
            else
            {
              // move tile to new location
              grid.moveTile(origTile, nextTile);
              MLOGD("TileGame", "tile moved.");
            }
          }
        }
      }
    }
  }

  MLOGD("TileGame", "MoveRight complete!");
  return true;
}

void Game::spawnTile() {
  // randomize later
  uint8_t col = 0;
  uint8_t row = 0;

  spawnTileAt(col, row);
}

void Game::spawnTileAt(uint8_t col, uint8_t row) {
  grid.tiles.at(col).at(row).rankUp();
  MLOGD("TileGame", "Tile spawned at (%d, %d)", col, row);
}

Game::Game() {
  // test lightup
  MLOGD("TileGame", "Game created");
}
