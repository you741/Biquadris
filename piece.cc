#include <utility>
#include "piece.h"

using namespace std;

int Piece::calculatePoints(int level) {
    return (level + 1) * (level + 1);
}

Piece::Piece(PieceCoords *coords, PieceType *pieceType, int level): coords{coords}, pieceType{pieceType}, points{calculatePoints(level)} {}

PieceCoords* Piece::rotatePiece(bool clockwise) {
    vector<pair<int,int>> newBlocks;
    int newHeight = coords->getWidth();
    int newWidth = coords->getHeight();
    int lowest = coords->getLowest();
    int leftmost = coords->getLeftmost();
    if(clockwise) {
        for(const auto &p: coords->getBlocks()) { // goes through every block and alters its x and y coordinates to rotate it clockwise
            int newX = leftmost + (p.second - lowest); // new X is based on old y and vice versa, we work with everything relative to bottom-left
            int newY = lowest + newHeight - (p.first - leftmost);
            newBlocks.emplace_back(make_pair(newX,newY));
        }
    } else {
        for(const auto &p: coords->getBlocks()) { // goes through every block and alters its x and y coordinates to rotate it counterclockwise
            int newX = leftmost + (lowest + coords->getHeight() - p.second);
            int newY = lowest + (p.first - leftmost);
            newBlocks.emplace_back(make_pair(newX,newY));
        }
    }
    return new PieceCoords(newBlocks);
}
