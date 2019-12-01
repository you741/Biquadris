#ifndef BOARD_INFO
#define BOARD_INFO 
#include <vector>
#include <stddef.h> 
#include "piececoords.h"
#include "cell.h"
#include "level.h"

struct BoardInfo {
    bool blind;
    int score;
    PieceCoords pc;
    std::vector<std::vector<Cell>> grid;
    Level level;
};

#endif
