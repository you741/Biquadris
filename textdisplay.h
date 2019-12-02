#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
// #include "observer.h"
#include "board.h"
// class Board;

class TextDisplay {
  std::vector<Board*> boards;
  void drawLevel(std::ostream& out);
  void drawScore(std::ostream& out);
  void drawGrid(std::ostream& out);
  void drawNext(std::ostream& out);
  void drawHorizontalLine(std::ostream& out);
 public:
  TextDisplay(std::vector<Board> &bs);
  void drawBoards(std::ostream& out);


//   friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
