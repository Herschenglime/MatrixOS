#include "Tile.h"

Color rankColorsData[] = {
  0x000000, 
  0xFF0000,
  0xFF8800,
  0xFFC800,
  0xF2FF00,
  0x6AFF00,
  0x00FFA2,
  0x00FFE6,
  0x00D9FF,
  0x0095FF,
  0x0051FF,
  0x000DFF,
  0x3700FF,
  0x7700FF,
  0xBB00FF,
  0xFF00FF
};

const Color* Tile::rankColors = rankColorsData;
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
    MatrixOS::LED::SetColor(point, rankColors[rank], 0);
  }
}

inline bool Tile::operator==(const Tile& other) const {
  return (this->rank == other.rank);
}

inline bool Tile::operator!=(const Tile& other) const {
  return !(*this == other);
}
