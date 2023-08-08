#pragma once

#include <vector>
#include "MatrixOS.h"

class Tile {
  static const Color* rankColors;
  // the individual matrix buttons that make up a tile
  vector<Point> subPoints;

  // the "score", for use in combinations
  uint8_t rank = 0;

  // the associated color of each rank (roygbiv for now)

  void light();

 public:
  // constructors
  Tile(vector<Point> points);
  Tile(Point p0, Point p1, Point p2, Point p3);

  const vector<Point> getSubPoints();
  void reset();
  uint8_t getRank() const;
  void rankUp();
  void setRank(uint8_t newRank);

  bool operator==(const Tile& other) const;
  bool operator!=(const Tile& other) const;

  int8_t col = -1;
  int8_t row = -1;
};
