#ifndef BOARD_INFO_H
#define BOARD_INFO_H
#include <vector>
#include <stddef.h>
#include "piece.h"
#include "cell.h"
#include "level.h"

struct BoardInfo {
    int height;
    int width;
    bool blind;
    int score;
    Piece *piece;
    Piece *nextPiece;
    const std::vector<std::vector<Cell>> &grid;
    int id;
    int level;
};

#endif
