#ifndef PIECE_H
#define PIECE_H
#include <memory>
#include <utility>
#include "piececoords.h"

enum class BlockType { I, Z, L, T, S, O, J };

class Piece {
    std::unique_ptr<PieceCoords> coords;
    int colour; // colour based on Xwindow's enum
    char sym; // symbol for text display
    int points; // points to give when this piece is cleared

    int calculatePoints(int level) const; // calculate points the piece is worth based on level
public:
    Piece(BlockType b, int x, int y, int level); // creates a piece based on a block type, a bottom left corner (x and y) and a level (for the score)
    int getColour() const;
    char getSym() const;
    void setCoords(PieceCoords* newCoords);
    PieceCoords* rotatePiece(bool clockwise = true) const; // returns coordinates that would've been gotten by rotating the piece
    PieceCoords* movePiece(int right = 0, int down = 0) const; // returns the coordinates that would've been gotten by moving the piece
};
#endif // PIECE_H
