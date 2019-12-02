#ifndef CELL_H
#define CELL_H
#include <memory>
#include "block.h"

class Cell { // a cell can either hold a block or it can be empty
    bool hasBlock = false; // does the cell have a block?
    std::unique_ptr<Block> block; // Cell can own a block
public:
    Cell(); // makes empty Cell
    Cell(Block* b); // makes a cell with a block
    Cell(const Cell &c);
    Cell(Cell &&c);
    Cell &operator=(Cell &&c);
    bool getHasBlock() const;
    Block* getBlock() const;
    void setBlock(Block* b);
    int removeBlockAndGetPoints(); // removes the block, if it's the last of its original piece then we get points
};
#endif // CELL_H
