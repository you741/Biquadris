#include "block.h"

Block::Block(std::pair<int,int> loc, int points, int colour, char sym): loc{loc}, points{points}, colour{colour}, sym{sym}, numNeighbours{0} {}

int Block::getRow() const {
    return loc.second;
}

int Block::getCol() const {
    return loc.first;
}

int Block::getPoints() const {
    return points;
}

int Block::getColour() const {
    return colour;
}

char Block::getSym() const {
    return sym;
}

void Block::removeNeighbour(Block *b) { // removes the requested neighbour from the array
    for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
        if (*it == b) {
            neighbours.erase(it);
            numNeighbours--;
            break;
        }
    }
}

void Block::addNeighbour(Block *b) { // adds a neighbour to the vector of neighbours
    neighbours.emplace_back(b);
    numNeighbours++;
}

int Block::removeSelfAndGetPoints() { // deletes itself from the its neighbours, or returns points if it has no more neighbours
    if(numNeighbours == 0) { // if it has no more neighbours, we just return the points as this is the final block being removed
        return points;
    } else {
        for(const auto &p: neighbours) {
            p->removeNeighbour(this); // removes itself from its neighbours
        }
        return 0;
    }
}
