#include "piececoords.h"

using namespace std;

PieceCoords::PieceCoords(vector<pair<int,int>> blocks): blocks{blocks} {
    // we now calculate the width height leftmost and lowest
    int leftmost = 2147483647, lowest = 2147483647, rightmost = -2147483648, highest = -2147483648;
    for(auto p: blocks) {
        if(p.first < leftmost) {
            leftmost = p.first;
        }
        if(p.first > rightmost) {
            rightmost = p.first;
        }
        if(p.second > highest) {
            highest = p.second;
        }
        if(p.second < lowest) {
            lowest = p.second;
        }
    }
    this->leftmost = leftmost;
    this->lowest = lowest;
    this->width = rightmost - leftmost + 1;
    this->height = highest - lowest + 1;
}

const vector<pair<int,int>>& PieceCoords::getBlocks() const {
    return blocks;
}
int PieceCoords::getWidth() const {
    return width;
}
int PieceCoords::getHeight() const {
    return height;
}
int PieceCoords::getLowest() const {
    return lowest;
}
int PieceCoords::getLeftmost() const {
    return leftmost;
}
