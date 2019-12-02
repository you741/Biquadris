#include "cell.h"

Cell::Cell() {}
Cell::Cell(Block *b): hasBlock{true}, block{b} {}
Cell::Cell(const Cell &c): hasBlock{c.hasBlock}, block{new Block{*c.block}} {}
Cell::Cell(Cell &&c): hasBlock{c.hasBlock}, block{std::move(c.block)} {}
Cell& Cell::operator=(const Cell &c) {
	hasBlock = c.hasBlock;
	block.reset(new Block{*c.block});
	return *this;
}
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
