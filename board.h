#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include "cell.h"
#include "piecesequence.h"

class Board {
    int lastCleared = 0; // the last turn a row was cleared
    int turn = 0; // the turn of the board. goes up by one every drop
    std::unique_ptr<Piece> curPiece;
    std::unique_ptr<Piece> nextPiece;
    std::vector<std::vector<Cell>> grid;
    PieceSequence seq; // the seq will let us generate next pieces
    int width;
    int height;
    bool heavy = false;
    bool blind = false;
    Level level;
    bool special = false; // if 2+ rows were cleared, we set this to true so Game can tell it needs a special effect
    bool lost = false; // did they lose the game
    int score = 0;

};
#endif // BOARD_H
