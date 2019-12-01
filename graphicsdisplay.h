#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "window.h"
#include "board.h"

class Board;

class GraphicsDisplay {
    Xwindow *xw = nullptr; // owns an Xwindow object
    std::vector<Board*> boards;
    void drawLevel(std::ostream& out);
    void drawScore(std::ostream& out);
    void drawHorizontalLine(std::ostream& out);
    void drawGrid(std::ostream& out);
    void drawNext(std::ostream& out);
 public:
     GraphicsDisplay(const std::vector<Board> &bs);
     void drawBoards(std::ostream& out);
     ~GraphicsDisplay();
};

#endif

