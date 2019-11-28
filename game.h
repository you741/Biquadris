#ifndef GAME_H
#define GAME_H

#include <vector>
#include "board.h"
#include "inputreader.h"
#include "graphicsdisplay.h"
#include "textdisplay.h"
#include "commandargs.h"

// Where the main driver of the game resides. 
// Holds all the information and handles transferring information between boards.


class Game{
    std::vector<Board> boards;
    int numBoards = 2;
    // unique_ptr<InputReader> input; // Old because of sequence command
    int whoseTurn = 0;
    int hiScore = 0;
    unique_ptr<GraphicsDisplay> graphics;
    unique_ptr<TextDisplay> td;
  public:
    Game(CommandArgs ca);
    // The core loop of the game, where input is read until a winner is decided
    void readInput(istream &in);
    void nextTurn();
    bool hasWon();
    int returnWinner();
    Board getBoard(int target);
};
#endif
