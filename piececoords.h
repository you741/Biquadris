#ifndef PIECECOORDS_H
#define PIECECOORDS_H
#include <vector>
#include <utility>


class PieceCoords{
  std::vector<std::pair<int,int>> blocks;
  int width;
  int height;
  int lowest;
  int leftmost;
 public:
//what goes in constructor
  PieceCoords(std::vector<std::pair<int,int>> blocks);
  std::vector<std::pair<int,int>> getBlocks();
  int getWidth();
  int getHeight();
  int getLowest();
  int getLeftmost();
};
#endif
