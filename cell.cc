#include "cell.h"

Cell::Cell(): hasBlock{false} {}
Cell::Cell(Block *b): hasBlock{true}, block{b} {}
Cell::Cell(const Cell &c): hasBlock{false} {} // we only ever create copies of empty Cells, no need to copy Block
Cell::Cell(Cell &&c): hasBlock{c.hasBlock}, block{std::move(c.block)} {}
Cell& Cell::operator=(Cell &&c) {
	hasBlock = c.hasBlock;
	block = std::move(c.block);
	return *this;
}
bool Cell::getHasBlock() const {
    return hasBlock;
}
Block* Cell::getBlock() const {
    return block.get();
}
void Cell::setBlock(Block *b) {
    block.reset(b);
    hasBlock = true;
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
