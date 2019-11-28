#include <utility>
#include "piecetype.h"
#include "piececoords.h"
#include "iblock.h"

using namespace std;

PieceType* PieceType::getPieceType(BlockType b) { // generates a specialized piece and returns a pointer to it
    if (b == BlockType::I) {
        return new I_Block();
    } else if (b == BlockType::J) {
        return new J_Block();
    } else if (b == BlockType::L) {
        return new L_Block();
    } else if (b == BlockType::O) {
        return new O_Block();
    } else if (b == BlockType::S) {
        return new S_Block();
    } else if (b == BlockType::T) {
        return new T_Block();
    } else {
        return new Z_Block();
    }
}

int PieceType::getColour() {
    return colour;
}
char PieceType::getSym() {
    return sym;
}
PieceCoords* PieceType::getCoords() { // returns a raw pointer, the actual coordinates are just used to generate block so we do not give the caller ownership
    return startingCoords.get();
}
