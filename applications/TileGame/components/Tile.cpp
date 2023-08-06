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

const vector<Point> Tile::getSubPoints() {
  return subPoints;
}

void Tile::reset() {
  rank = 0;
}

void Tile::rankUp() {
  rank++;
  light();
}

void Tile::light() {
  for (Point point : subPoints) {
      MatrixOS::LED::SetColor(point, rankColors.at(rank), 0); 
  }
}
