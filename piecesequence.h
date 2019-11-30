#ifndef PIECESEQUENCE_H
#define PIECESEQUENCE_H
#include <fstream>
#include <string>
#include <memory>
#include <cstdlib>
#include "piece.h"
#include "level.h"

class PieceSequence { // this class can determine what the next piece is based on the level
    std::ifstream file; // the file that the sequence reads from
    bool random = false; // whether we use probabilities to calculate the next piece or not
    std::unique_ptr<Level> level; // the level of the board that owns this PieceSequence
public:
    PieceSequence(int lvl = 0);
    PieceSequence(std::string filename, int lvl = 0);
    PieceSequence(bool random, int lvl = 0);
    Piece* getPiece();
    void setFile(std::string filename); // sets the file stream
};
#endif // PIECESEQUENCE_H
