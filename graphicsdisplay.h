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
    // enum { White = 0, Black, Red, Green, Blue, Cyan, Yellow, Magenta,
		// Orange, Brown, DarkGreen }; // Available colours.



    // std::vector <Board*> boards;
    std::vector <Xwindow*> xw;

    std::vector <std::vector <std::vector <int>>> state;
    std::vector <std::vector <std::vector <int>>> oldState;

    // std::vector <BoardInfo> boardInfos;


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
    void drawGrid(int id);
    void setState(int id, const std::vector<std::vector<Cell>> &grid, Piece *piece, bool blind, int width, int height);
 public:
     GraphicsDisplay(std::vector<Board> &bs);
     void updateDisplay(int id);
     void notify(Subject<BoardInfo, BoardState> &whoFrom) override;// Board will call this

     ~GraphicsDisplay();
};

#endif
