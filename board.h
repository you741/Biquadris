#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include "cell.h"

class Board {
    std::unique_ptr<Piece> curPiece;
    std::unique_ptr<Piece> nextPiece;
    std::vector<std::vector<Cell>> grid;
};
#endif // BOARD_H
