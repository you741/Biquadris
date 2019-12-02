#ifndef PIECE_H
#define PIECE_H
#include <memory>
#include <utility>
#include <vector>
#include "block.h"
#include "piececoords.h"

class Piece {
    std::unique_ptr<PieceCoords> coords;
    int colour; // colour based on Xwindow's enum
    char sym; // symbol for text display
    int points; // points to give when this piece is cleared
    bool heavy = false;

    int calculatePoints(int level) const; // calculate points the piece is worth based on level
public:
    Piece(BlockType b, int x, int y, int level, bool heavy = false); // creates a piece based on a block type, a bottom left corner (x and y) and a level (for the score)
    int getColour() const;
    char getSym() const;
    const std::vector<std::pair<int,int>> &getBlocks() const;
    int getWidth() const;
    int getHeight() const;
    int getLowest() const;
    int getLeftmost() const;
    bool isHeavy() const;
    void setCoords(std::unique_ptr<PieceCoords> &&newCoords);
    PieceCoords* rotatePiece(bool clockwise = true) const; // returns coordinates that would've been gotten by rotating the piece
    PieceCoords* movePiece(int right = 0, int down = 0) const; // returns the coordinates that would've been gotten by moving the piece
    PieceCoords* getCoords();
    bool hasCoord(std::pair<int,int> p) const; // returns whether the piece has the coordinate or not
    std::vector<Block*> makeBlocks() const; // makes blocks out of the piece's coordinates
};
#endif // PIECE_H
