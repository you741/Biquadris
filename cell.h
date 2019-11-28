#ifndef CELL_H
#define CELL_H
#include <memory>

class Cell { // a cell can either hold a block or it can be empty
    bool hasBlock = false;
    std::unique_ptr<Block> block;
public:
    bool getHasBlock() const;
    Block* getBlock() const;
    int removeBlockAndGetPoints();
};
#endif // CELL_H
