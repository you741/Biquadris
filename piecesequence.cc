#include "piecesequence.h"

using namespace std;

PieceSequence::PieceSequence(std::string filename, int lvl): file{filename}, level{make_unique<Level>(lvl)} {}
PieceSequence::PieceSequence(bool random, int lvl): random{random}, level{make_unique<Level>(lvl)} {}
Piece* PieceSequence::getPiece() {
    // TODO: complete the probability and stuff here to return a piece
}
void PieceSequence::setFile(std::string filename){
    file = ifstream(filename);
} // sets the file stream
