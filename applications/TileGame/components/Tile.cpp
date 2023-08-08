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
  light();
}

uint8_t Tile::getRank() const {
  return rank;
}

void Tile::rankUp() {
  rank++;
  light();
}

void Tile::setRank(uint8_t newRank) {
  rank = newRank;
  light();
}

void Tile::light() {
  for (Point point : subPoints)
  {
    MatrixOS::LED::SetColor(point, rankColors.at(rank), 0);
  }
}

inline bool Tile::operator==(const Tile& other) const {
  return (this->rank == other.rank);
}

inline bool Tile::operator!=(const Tile& other) const {
  return !(*this == other);
}
