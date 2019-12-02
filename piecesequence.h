#ifndef PIECESEQUENCE_H
#define PIECESEQUENCE_H
#include <fstream>
#include <string>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include "piece.h"
#include "level.h"

class PieceSequence { // this class can determine what the next piece is based on the level
    std::string filename;
    std::ifstream file; // the file that the sequence reads from
    bool random = false; // whether we use probabilities to calculate the next piece or not
    std::unique_ptr<Level> level; // the level of the board that owns this PieceSequence
    bool hasSeed = false;
    int seed = 1;
    int height = 15; // height is required to find the top left corner
public:
    PieceSequence(int lvl = 0, bool hasSeed = false, int seed = 1, int height = 15);
    PieceSequence(std::string filename, int lvl = 0, bool hasSeed = false, int seed = 1, int height = 15);
    PieceSequence(bool random, int lvl = 0, bool hasSeed = false, int seed = 1, int height = 15);
    Piece* getPiece();
    void setLevel(int lvl);
    void setFile(std::string filename); // sets the file stream
    void setRandom(bool random);
};
#endif // PIECESEQUENCE_H
