#ifndef PIECE_H
#define PIECE_H
#include <memory>
#include "piececoords.h"
#include "piecetype.h"
class Piece {
    std::unique_ptr<PieceCoords> coords;
    std::unique_ptr<PieceType> pieceType;
    int points;

    int calculatePoints(int level);
public:
    Piece(PieceCoords *coords, PieceType *pieceType, int level);
    PieceCoords* rotatePiece(bool clockwise = true);

};
#endif // PIECE_H
