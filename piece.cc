#include <utility>
#include <vector>
#include "piece.h"
#include "window.h"
#include <iostream>

using namespace std;

int Piece::calculatePoints(int level) const {
    return (level + 1) * (level + 1);
}

Piece::Piece(BlockType b, int x, int y, int level, bool heavy): points{calculatePoints(level)}, heavy{heavy} { // generates the fields based on the block type
    if (b == BlockType::I) {
        this->colour = Xwindow::Orange;
        this->sym = 'I';
        this->coords = unique_ptr<PieceCoords>(new PieceCoords{vector<pair<int,int>>{make_pair(x,y), make_pair(x+1,y), make_pair(x+2,y), make_pair(x+3,y)}});
    } else if (b == BlockType::J) {
        this->colour = Xwindow::Magenta;
	this->sym = 'J';
        this->coords = unique_ptr<PieceCoords>(new PieceCoords{vector<pair<int,int>>{make_pair(x,y+1), make_pair(x,y), make_pair(x+1,y), make_pair(x+2,y)}});
    } else if (b == BlockType::L) {
        this->colour = Xwindow::DarkGreen;
        this->sym = 'L';
        this->coords = unique_ptr<PieceCoords>(new PieceCoords{vector<pair<int,int>>{make_pair(x,y), make_pair(x+1,y), make_pair(x+2,y), make_pair(x+2,y+1)}});
    } else if (b == BlockType::O) {
        this->colour = Xwindow::Green;
        this->sym = 'O';
        this->coords = unique_ptr<PieceCoords>(new PieceCoords{vector<pair<int,int>>{make_pair(x,y), make_pair(x+1,y), make_pair(x+1,y+1), make_pair(x,y+1)}});
    } else if (b == BlockType::S) {
        this->colour = Xwindow::Red;
        this->sym = 'S';
        this->coords = unique_ptr<PieceCoords>(new PieceCoords{vector<pair<int,int>>{make_pair(x,y), make_pair(x+1,y), make_pair(x+1,y+1), make_pair(x+2,y+1)}});
    } else if (b == BlockType::T) {
        this->colour = Xwindow::Yellow;
        this->sym = 'T';
        this->coords = unique_ptr<PieceCoords>(new PieceCoords{vector<pair<int,int>>{make_pair(x,y+1), make_pair(x+1,y+1), make_pair(x+2,y+1), make_pair(x+1,y)}});
    } else {
        this->colour = Xwindow::Cyan;
        this->sym = 'Z';
        this->coords = unique_ptr<PieceCoords>(new PieceCoords{vector<pair<int,int>>{make_pair(x+1,y), make_pair(x,y+1), make_pair(x+1,y+1), make_pair(x+2,y)}});
    }
}

int Piece::getColour() const {
    return colour;
}

char Piece::getSym() const {
    return sym;
}

PieceCoords* Piece::getCoords() { // returns a raw pointer, the actual coordinates are just used to generate blocks so we do not give the caller ownership
    return coords.get();
}

const vector<pair<int,int>>& Piece::getBlocks() const {
    return coords->getBlocks();
}

int Piece::getWidth() const {
    return coords->getWidth();
}

int Piece::getHeight() const {
    return coords->getHeight();
}

int Piece::getLowest() const {
    return coords->getLowest();
}

int Piece::getLeftmost() const {
    return coords->getLeftmost();
}

bool Piece::isHeavy() const {
    return heavy;
}

void Piece::setCoords(unique_ptr<PieceCoords> &&pc) {
    coords = move(pc); // takes ownership of the new coordinates. The old one is destroyed
}

PieceCoords* Piece::rotatePiece(bool clockwise) const { // returns coordinates the piece would have if it was rotated either clockwise or counterclockwise
    vector<pair<int,int>> newBlocks;
    int newHeight = coords->getWidth();
    // int newWidth = coords->getHeight();
    int lowest = coords->getLowest();
    int leftmost = coords->getLeftmost();
    if(clockwise) {
        for(const auto &p: coords->getBlocks()) { // goes through every block and alters its x and y coordinates to rotate it clockwise
            int newX = leftmost + (p.second - lowest); // new X is based on old y and vice versa, we work with everything relative to bottom-left
            int newY = lowest + newHeight - 1 - (p.first - leftmost);
            newBlocks.emplace_back(make_pair(newX,newY));
        }
    } else {
        for(const auto &p: coords->getBlocks()) { // goes through every block and alters its x and y coordinates to rotate it counterclockwise
            int newX = leftmost + (lowest + coords->getHeight() - 1 - p.second);
            int newY = lowest + (p.first - leftmost);
            newBlocks.emplace_back(make_pair(newX,newY));
        }
    }
    return new PieceCoords{newBlocks};
}

PieceCoords* Piece::movePiece(int right, int down) const { // returns coordinates piece would have if it moved by the specifications
    vector<pair<int,int>> newBlocks;
    for(const auto &p: coords->getBlocks()) {
        newBlocks.emplace_back(make_pair(p.first + right, p.second - down));
    }
    return new PieceCoords{newBlocks};
}

bool Piece::hasCoord(pair<int,int> p) const {
    for(const auto &b: coords->getBlocks()) {
        if (p == b) { // if the pair exists then we return true
            return true;
        }
    }
    return false;
}

vector<Block*> Piece::makeBlocks() const { // generates a vector of block pointers
    vector<Block*> newBlocks;
    for(const auto &p: coords->getBlocks()) { // first adds a block for every coordinate
        newBlocks.emplace_back(new Block{p, points, colour, sym});
    }
    for(auto block: newBlocks) { // next add the other blocks to each block as a neighbour
        for(auto neighbour: newBlocks) {
            if(block != neighbour) {
                block->addNeighbour(neighbour); // adds all the other blocks as neighbours except for itself
            }
        }
    }
    return newBlocks;
}
