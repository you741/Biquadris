#include "piecesequence.h"

using namespace std;
PieceSequence::PieceSequence(int lvl): level{new Level{lvl}} {
    this->random = level->isRandom(); // default value of random
}
PieceSequence::PieceSequence(std::string filename, int lvl): file{filename}, level{new Level{lvl}} {
    this->random = level->isRandom(); // sets if the level should be random or not (default value)
}
PieceSequence::PieceSequence(bool random, int lvl): random{random}, level{new Level{lvl}} {}

Piece* PieceSequence::getPiece() { // generates a piece based on random and the Level
    // all the probabilities are here
}
void PieceSequence::setFile(std::string filename){
    file = ifstream(filename);
} // sets the file stream
