#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "window.h"
#include "board.h"

class Board;

class GraphicsDisplay {

    std::vector <*Board> boards;
    std::vector <*Xwindow> xw;
    
    const size_t leftIndent = 20;
    const size_t topIndent = 20;
    const size_t lineBreak = 15;
    const size_t cellWidth = 20;
    const size_t boardWidth = 11;
    const size_t boardHeight = 18;
    const size_t slIndent = 50;

    const std::vector<string> colours = {'W', 'B', 'I', 'J', 'L', 'O', 'S', 'Z', 'T'},

    void init(size_t id);
    void updateLevel(size_t id);
    void updateScore(size_t id);
    void updateGrid(size_t id);
    void updateNext(size_t id);
 public:
     GraphicsDisplay(const std::vector<Board> &bs);
     void updateBoard(size_t id);
     ~GraphicsDisplay();
};

#endif
