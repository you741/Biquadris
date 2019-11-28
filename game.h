#ifndef GAME_H
#define GAME_H
#include <vector>
#include "board.h"
#include "inputreader.h"


class Game{
    std::vector<Board> boards;
    int numBoards;
    InputReader input;
    int whoseTurn;
    int hiScore;
    GraphicsDisplay graphics;
    TextDisplay td;
  public:
    Game(bool textOnly, int seed, string scriptfile1, string scriptfile2, int startLevel);
    void readInput(bool special);
    void nextTurn();
    bool hasWon();
    int returnWinner();
    Board getBoard(int target);
};
#endif
