#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "window.h"
#include "board.h"

class Board;

class GraphicsDisplay {
    enum { White = 0, Black, Red, Green, Blue, Cyan, Yellow, Magenta,
		Orange, Brown, DarkGreen }; // Available colours.

    std::vector <Board*> boards;
    std::vector <Xwindow*> xw;

    std::vector <std::vector <std::vector <int>>> state;
    std::vector <std::vector <std::vector <int>>> oldState;


    const int leftIndent = 20;
    const int topIndent = 20;
    const int lineBreak = 15;
    const int cellWidth = 20;
    const int boardWidth = 11;
    const int boardHeight = 18;
    const int slIndent = 50;

    void init(int id);
    void updateLevel(int id);
    void updateScore(int id);
    void updateGrid(int id);
    void updateNext(int id);
    void drawGrid(int id);
    void setState(int id);
 public:
     GraphicsDisplay(std::vector<Board> &bs);
     void updateDisplay(int id);
     ~GraphicsDisplay();
};

#endif
