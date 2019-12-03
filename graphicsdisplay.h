#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "window.h"
#include "board.h"
#include "boardinfo.h"
#include "boardstate.h"
#include "observer.h"

class Board;

class GraphicsDisplay: public Observer<BoardInfo, BoardState>{
    // std::vector <Board*> boards;
    std::vector <std::unique_ptr<Xwindow>> xw;

    //save the state of grids to only update what is necessary
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
    void updateLevel(int id, int level);
    void updateScore(int id, int score);
    void updateGrid(int id, int width, int height);
    void updateNext(int id, Piece *nextPiece, int height);
    void drawGrid(int id); // draw the initial grid lines
    void setState(int id, const std::vector<std::vector<Cell>> &grid, Piece *piece, bool blind, int width, int height); // set the grid state with correct colours
 public:
     GraphicsDisplay(std::vector<Board> &bs); 
     void notify(Subject<BoardInfo, BoardState> &whoFrom) override;// Board will call this

    //  ~GraphicsDisplay();
};

#endif
