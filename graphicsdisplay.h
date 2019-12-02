#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "window.h"
#include "board.h"

class Board;

class GraphicsDisplay {

    std::vector <Board*> boards;
    std::vector <Xwindow*> xw;

    const int leftIndent = 20;
    const int topIndent = 20;
    const int lineBreak = 15;
    const int cellWidth = 20;
    const int boardWidth = 11;
    const int boardHeight = 18;
    const int slIndent = 50;

    const std::vector<char> colours {'W', 'B', 'I', 'J', 'L', 'O', 'S', 'Z', 'T'};

    void init(int id);
    void updateLevel(int id);
    void updateScore(int id);
    void updateGrid(int id);
    void updateNext(int id);
 public:
     GraphicsDisplay(std::vector<Board> &bs);
     void updateDisplay(int id);
     ~GraphicsDisplay();
};

#endif
