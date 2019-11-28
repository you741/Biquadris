#include "cell.h"

bool Cell::getHasBlock() const {
    return hasBlock;
}
Block* Cell::getBlock() const {
    return block.get();
}
    int removeBlockAndGetPoints();
