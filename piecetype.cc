#include <utility>
#include "piecetype.h"
#include "piececoords.h"

using namespace std;

PieceType(Colour colour, char sym, PieceCoords startingCoords);

PieceType PieceType::getPieceType(BlockType b) {
    if (b == BlockType::I) {
        return I_Block()
    }
}


