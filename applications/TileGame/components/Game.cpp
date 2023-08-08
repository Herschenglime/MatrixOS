#include <algorithm>
#include <utility>

using std::pair;

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
    spawnTileAt(3, 0);
    spawnTileAt(1, 1);
    spawnTileAt(2, 2);
    spawnTileAt(3, 3);
  }
  else
  {
    processBoard();
  }

  MLOGD("TileGame", "Game initiated");
}

bool Game::moveLeft() {
  // keep track of whether any tiles actually moved (to control spawning)
  bool tileMoved = false;

  // move each tile from left to right in each column
  for (int8_t colNum = 0; colNum < 4; colNum++)
  {
    auto& column = grid.tiles.at(colNum);

    for (uint8_t rowNum = 0; rowNum < 4; rowNum++)
    {
      Tile& origTile = column.at(rowNum);
      MLOGD("TileGame", "Original tile is at (%d, %d) and has rank %d", colNum, rowNum, origTile.getRank());

      //   only move tile if there's something there (i.e. has rank)
      if (origTile.getRank() > 0)
      {
        // only tiles not on the left edge can move (int to handle negative bounds)
        int8_t prevCol = colNum - 1;

        if (prevCol > -1)
        {
          Tile* prevTilePtr = &grid.tiles.at(prevCol).at(rowNum);
          MLOGD("TileGame", "Next tile is at (%d, %d) and has rank %d", prevCol, rowNum, prevTilePtr->getRank());

          // check rank of tile to the right
          // if 0, look for the next one (keeping in mind boundaries of grid)
          while (prevTilePtr->getRank() == 0 && prevCol > 0)
          {
            prevTilePtr = &grid.tiles.at(--prevCol).at(rowNum);
            MLOGD("TileGame", "Col of prevTile is %d", prevCol);
          }

          auto& prevTile = *prevTilePtr;
          MLOGD("TileGame", "Tile for comparison is at (%d, %d) and has rank %d", prevCol, rowNum, prevTile.getRank());
          if (prevTile.getRank() == 0)
          {
            // move tile to new location
            grid.moveTile(origTile, prevTile);
            MLOGD("TileGame", "tile moved to edge.");

            tileMoved = true;
          }
          // if not on the right edge, compare current tile
          else if (origTile.getRank() == prevTile.getRank())
          {
            grid.combineTiles(origTile, prevTile);
            tileMoved = true;
          }
          else
          {
            // check if tile actually moves
            if (colNum == ++prevCol)
            {
              MLOGD("TileGame", "tile couldn't move.");
            }

            else
            {
              // move tile to column before next tile of different rank
              grid.moveTile(origTile, grid.tiles.at(prevCol).at(rowNum));
              MLOGD("TileGame", "tile moved.");
            }
          }
        }

        else
        {
          MLOGD("TileGame", "tile was already at edge.");
        }
      }
    }
  }

  MLOGD("TileGame", "MoveLeft complete!");
  return tileMoved;
}

bool Game::moveRight() {
  // keep track of whether any tiles actually moved (to control spawning)
  bool tileMoved = false;

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
          if (nextTile.getRank() == 0)
          {
            // move tile to new location
            grid.moveTile(origTile, nextTile);
            MLOGD("TileGame", "tile moved to edge.");

            tileMoved = true;
          }
          // if not on the right edge, compare current tile
          else if (origTile.getRank() == nextTile.getRank())
          {
            grid.combineTiles(origTile, nextTile);
            tileMoved = true;
          }
          else
          {
            // check if tile actually moves
            if (colNum == --nextCol)
            {
              MLOGD("TileGame", "tile couldn't move.");
            }

            else
            {
              // move tile to column before next tile of different rank
              grid.moveTile(origTile, grid.tiles.at(nextCol).at(rowNum));
              MLOGD("TileGame", "tile moved.");
            }
          }
        }

        else
        {
          MLOGD("TileGame", "tile was already at edge.");
        }
      }
    }
  }

  MLOGD("TileGame", "MoveRight complete!");
  return tileMoved;
}

bool Game::moveDown() {
  // keep track of whether any tiles actually moved (to control spawning)
  bool tileMoved = false;

  // move each tile from bottom to top in each row
  for (int8_t rowNum = 3; rowNum >= 0; rowNum--)
  {
    vector<Tile*> row;
    row.reserve(4);
    for (uint8_t i = 0; i < 4; i++)
    {
      row.push_back(&grid.tiles.at(i).at(rowNum));
    }

    for (uint8_t colNum = 0; colNum < 4; colNum++)
    {
      Tile& origTile = *row.at(colNum);
      MLOGD("TileGame", "Original tile is at (%d, %d) and has rank %d", colNum, rowNum, origTile.getRank());

      //   only move tile if there's something there (i.e. has rank)
      if (origTile.getRank() > 0)
      {
        // only tiles not on the right edge can move
        uint8_t nextRow = rowNum + 1;

        if (nextRow < 4)
        {
          Tile* nextTilePtr = &grid.tiles.at(colNum).at(nextRow);
          MLOGD("TileGame", "Next tile is at (%d, %d) and has rank %d", colNum, nextRow, nextTilePtr->getRank());

          // check rank of tile below
          // if 0, look for the next one (keeping in mind boundaries of grid)
          while (nextTilePtr->getRank() == 0 && nextRow < 3)
          {
            nextTilePtr = &grid.tiles.at(colNum).at(++nextRow);
            MLOGD("TileGame", "Row of nextTile is %d", nextRow);
          }

          auto& nextTile = *nextTilePtr;
          MLOGD("TileGame", "Tile for comparison is at (%d, %d) and has rank %d", colNum, nextRow, nextTile.getRank());
          if (nextTile.getRank() == 0)
          {
            // move tile to new location
            grid.moveTile(origTile, nextTile);
            MLOGD("TileGame", "tile moved to edge.");

            tileMoved = true;
          }
          // if not on the bottom edge, compare current tile
          else if (origTile.getRank() == nextTile.getRank())
          {
            grid.combineTiles(origTile, nextTile);
            tileMoved = true;
          }
          else
          {
            // check if tile actually moves
            if (rowNum == --nextRow)
            {
              MLOGD("TileGame", "tile couldn't move.");
            }

            else
            {
              // move tile to column before next tile of different rank
              grid.moveTile(origTile, grid.tiles.at(colNum).at(nextRow));
              MLOGD("TileGame", "tile moved.");
            }
          }
        }

        else
        {
          MLOGD("TileGame", "tile was already at edge.");
        }
      }
    }
  }

  MLOGD("TileGame", "MoveDown complete!");
  return tileMoved;
}
bool Game::moveUp() {
  // keep track of whether any tiles actually moved (to control spawning)
  bool tileMoved = false;

  // move each tile from top to bottom in each row
  for (int8_t rowNum = 0; rowNum < 4; rowNum++)
  {
    // make convenience vector to make code more copyable from other move methods
    vector<Tile*> row;
    row.reserve(4);
    for (uint8_t i = 0; i < 4; i++)
    {
      row.push_back(&grid.tiles.at(i).at(rowNum));
    }

    for (uint8_t colNum = 0; colNum < 4; colNum++)
    {
      Tile& origTile = *row.at(colNum);
      MLOGD("TileGame", "Original tile is at (%d, %d) and has rank %d", colNum, rowNum, origTile.getRank());

      //   only move tile if there's something there (i.e. has rank)
      if (origTile.getRank() > 0)
      {
        // only tiles not on the right edge can move
        int8_t prevRow = rowNum - 1;

        if (prevRow > -1)
        {
          Tile* prevTilePtr = &grid.tiles.at(colNum).at(prevRow);
          MLOGD("TileGame", "Prev tile is at (%d, %d) and has rank %d", colNum, prevRow, prevTilePtr->getRank());

          // check rank of tile below
          // if 0, look for the next one (keeping in mind boundaries of grid)
          while (prevTilePtr->getRank() == 0 && prevRow > 0)
          {
            prevTilePtr = &grid.tiles.at(colNum).at(--prevRow);
            MLOGD("TileGame", "Row of prevTile is %d", prevRow);
          }

          auto& prevTile = *prevTilePtr;
          MLOGD("TileGame", "Tile for comparison is at (%d, %d) and has rank %d", colNum, prevRow, prevTile.getRank());
          if (prevTile.getRank() == 0)
          {
            // move tile to new location
            grid.moveTile(origTile, prevTile);
            MLOGD("TileGame", "tile moved to edge.");

            tileMoved = true;
          }
          // if not on the bottom edge, compare current tile
          else if (origTile.getRank() == prevTile.getRank())
          {
            grid.combineTiles(origTile, prevTile);
            tileMoved = true;
          }
          else
          {
            // check if tile actually moves
            if (rowNum == ++prevRow)
            {
              MLOGD("TileGame", "tile couldn't move.");
            }

            else
            {
              // move tile to column before next tile of different rank
              grid.moveTile(origTile, grid.tiles.at(colNum).at(prevRow));
              MLOGD("TileGame", "tile moved.");
            }
          }
        }

        else
        {
          MLOGD("TileGame", "tile was already at edge.");
        }
      }
    }
  }

  MLOGD("TileGame", "MoveUp complete!");
  return tileMoved;
}

//TODO: Optimize removal of empty tiles, particularly with random spawn and knowing the index
//also fix crashing 
void Game::processBoard() {
  //create vector of empty tile coords
  vector<pair<uint8_t, uint8_t>> emptyCoords;

  // go through tiles and grab coords of empty tiles
  for (auto& column : grid.tiles) {
    for (auto& tile : column) {

    }
  }

  spawnTileAt(0,0);
}

void Game::spawnTileAt(uint8_t col, uint8_t row) {
  auto& tile = grid.tiles.at(col).at(row);
  spawnTileAt(tile);
}

void Game::spawnTileAt(Tile& tile) {
  tile.rankUp();

  MLOGD("TileGame", "Tile spawned at (%d, %d)", tile.col, tile.row);
}

Game::Game() {
  // test lightup
  MLOGD("TileGame", "Game created");
}
