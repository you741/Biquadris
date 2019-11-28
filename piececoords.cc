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

vector<pair<int,int>> PieceCoords::getBlocks() {
    return blocks;
}
int PieceCoords::getWidth() {
    return width;
}
int PieceCoords::getHeight() {
    return height;
}
int PieceCoords::getLowest() {
    return lowest;
}
int PieceCoords::getLeftmost() {
    return leftmost;
}
