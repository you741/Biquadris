#ifndef PIECETYPE_H
#define PIECETYPE_H
#include <vector>
#include <memory>
#include "piececoords.h"
#include "window.h"

enum class BlockType { I, Z, L, T, S, O, J };

class PieceType{ // stores everything required to know the specifics of specific piece
  protected:
    int colour; // colour based on Xwindow's enum
    char sym; // symbol for text display
    std::unique_ptr<PieceCoords> startingCoords; // owns the starting coordinates
  public:
    static PieceType* getPieceType(BlockType b); // factory method of generating a PieceType based on a BlockType
    int getColour();
    char getSym();
    PieceCoords *getCoords();
};
#endif
