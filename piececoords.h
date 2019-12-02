#ifndef PIECECOORDS_H
#define PIECECOORDS_H
#include <vector>
#include <utility>

class PieceCoords { // this class stores the coordinates of every block in the piece, meant as a form of data
  std::vector<std::pair<int,int>> blocks; // stores the coordinates of every block
  // dimensions and coordinates of the smallest rectangle that fits the piece
  int width;
  int height;
  int lowest;
  int leftmost;
 public:
  PieceCoords(std::vector<std::pair<int,int>> blocks);
  const std::vector<std::pair<int,int>> &getBlocks() const;
  int getWidth() const;
  int getHeight() const;
  int getLowest() const;
  int getLeftmost() const;
};
#endif
