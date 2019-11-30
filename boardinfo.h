#ifndef BOARD_INFO
#define BOARD_INFO 
#include <stddef> 

struct BoardInfo {
    bool blind;
    int score;
    PieceCoords pc;
    vector<std::vector<Cell>> grid;
    Level level;
};

#endif
