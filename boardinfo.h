#ifndef BOARD_INFO_H
#define BOARD_INFO_H
#include <vector>
#include <stddef.h>
#include "piececoords.h"
#include "cell.h"
#include "level.h"

struct BoardInfo {
    bool blind;
    int score;
    PieceCoords *pc;
    const std::vector<std::vector<Cell>> &grid;
    int level;
};

#endif
