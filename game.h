#ifndef GAME_H
#define GAME_H

#include <utility>
#include <vector>
#include <iostream>
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
    bool textOnly = false;
    std::unique_ptr<GraphicsDisplay> graphics;
    std::unique_ptr<TextDisplay> td;

    void updateDisplay(int id);
  public:
    Game(CommandArgs ca);
    // The core loop of the game, where input is read until a winner is decided
    void readInput(std::istream &in);
    void nextTurn();
    bool hasWon();
    int returnWinner();
    Board& getBoard(int target);
};
#endif
