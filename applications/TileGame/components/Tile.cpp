#include "Tile.h"


Tile::Tile(vector<Point> points) {
  subPoints = points;
}

Tile::Tile(Point p0, Point p1, Point p2, Point p3) {
  subPoints.push_back(p0);
  subPoints.push_back(p1);
  subPoints.push_back(p2);
  subPoints.push_back(p3);
}