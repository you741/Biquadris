#include "cell.h"

bool Cell::getHasBlock() const {
    return hasBlock;
}
Block* Cell::getBlock() const {
    return block.get();
}
int Cell::removeBlockAndGetPoints() {
    if(hasBlock) {
        hasBlock = false; // sets hasBlock to false
        int points = block->removeSelfAndGetPoints(); // gets the points scored by the blocks if it was the last one of its original piece, also removes itself from all its neighbours
        block.reset(); // gets rid of the block in this cell
        return points;
    } else { // no block then does nothing, return 0
        return 0;
    }
}
