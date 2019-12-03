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
    CommandArgs ca;
    std::vector<Board> boards;
    int numBoards = 2;
    // unique_ptr<InputReader> input; // Old because of sequence command
    int whoseTurn = 0;
    int hiScore = 0;
    bool textOnly = false;
    int winnerScore = -1;
    std::unique_ptr<GraphicsDisplay> graphics;
    std::unique_ptr<TextDisplay> td;

    void updateDisplay(int id); // updates textdisplay
    bool readSpecialCommand(std::istream &in); // returns false if it hits an EOF
  public:
    Game(CommandArgs ca);
    // The core loop of the game, where input is read until a winner is decided
    bool readInput(std::istream &in); // returns true if it asks for special
    void nextTurn();
    bool hasWon();
    int returnWinner();
    int getWinnerScore();
    Board& getBoard(int target);
};
#endif
