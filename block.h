#ifndef BLOCK_H
#define BLOCK_H
#include <utility>
#include <vector>

enum BlockType {
 Z='Z',
 T='T',
 I='I',
 J='J',
 L='L',
 O='O',
 S='S'
};

class Block {
    std::pair<int,int> loc; // where the block is stored
    std::vector<Block*> neighbours; // where are the neighbors
    int points; // points the block is worth
    int colour; // colour of the block
    char sym; // symbol of the block for text display
    int numNeighbours; // number of neighbours we have
public:
    Block(std::pair<int,int> loc, int points, int colour, char sym);
    int getRow() const;
    int getCol() const;
    int getPoints() const;
    int getColour() const;
    char getSym() const;
    void removeNeighbour(Block *b); // removes the specified neighbour
    void addNeighbour(Block *b); // adds a neighbour to our list
    int removeSelfAndGetPoints(); // removes this block from all its neighbours and returns points if it is the last of its original piece

};
#endif
