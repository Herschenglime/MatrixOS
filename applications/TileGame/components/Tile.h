#pragma once

#include <vector>
#include "MatrixOS.h"

struct Tile {
  vector<Point> subPoints;
  Tile(vector<Point> points);
  Tile(Point p0, Point p1, Point p2, Point p3);
};
