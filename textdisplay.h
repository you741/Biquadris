#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "boardstate.h"
#include "boardinfo.h"
class Board;

class TextDisplay {
  std::vector<Board*> boards;

  //Width of a board
  const w = 12;

 public:
  TextDisplay(int n);

//   friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
