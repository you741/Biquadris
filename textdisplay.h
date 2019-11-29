#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
class Board;

class TextDisplay: public Observer<Info, State> {
  std::vector<Board*> boards;

  //Width of a board
  const w = 12;

 public:
  TextDisplay(int n);

  void notify(Subject<BoardInfo, BoardState> &whoNotified) override;

//   friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
