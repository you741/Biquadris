#include "piecesequence.h"
#include "board.h"
#include "block.h"

using namespace std;

PieceSequence::PieceSequence(int lvl): level{new Level{lvl}} {
    this->random = level->isRandom(); // default value of random
}
PieceSequence::PieceSequence(std::string filename, int lvl): file{filename}, level{new Level{lvl}} {
    this->random = level->isRandom(); // sets if the level should be random or not (default value)
}
PieceSequence::PieceSequence(bool random, int lvl): random{random}, level{new Level{lvl}} {}

Piece* PieceSequence::getPiece() { // generates a piece based on random and the Level and places it on the top left corner
    // all the probabilities are here
    char nextBlockType; // the next Piece type, it will create it based on a BlockType
    if(level->getLevel() == 0 || !random) { // it needs to be nonrandom here (level 0 has to be nonrandom)
        file >> nextBlockType;
    } else { // then it is a random generation
        int r = rand();
        // LEVEL 1
        if(level->getLevel() == 1) {
            if(r%12 == 0) {
                nextBlockType = 'S';
            } else if (r%12 == 1) {
                nextBlockType = 'Z';
            } else if (r%12 <= 3) {
                nextBlockType = 'T';
            } else if (r%12 <= 5) {
                nextBlockType = 'L';
            } else if (r%12 <= 7) {
                nextBlockType = 'J';
            } else if (r%12 <= 9) {
                nextBlockType = 'I';
            } else {
                nextBlockType = 'O';
            }
        }
        // LEVEL 2
        if(level->getLevel() == 2) {
            if(r%7 == 0) {
                nextBlockType = 'S';
            } else if (r%7 == 1) {
                nextBlockType = 'Z';
            } else if (r%7 == 2) {
                nextBlockType = 'T';
            } else if (r%7 == 3) {
                nextBlockType = 'L';
            } else if (r%7 == 4) {
                nextBlockType = 'J';
            } else if (r%7 == 5) {
                nextBlockType = 'I';
            } else {
                nextBlockType = 'O';
            }
        }
        // LEVEL 3
        if(level->getLevel() == 3) {
            if(r%9 <= 1) {
                nextBlockType = 'S';
            } else if (r%9 <= 3) {
                nextBlockType = 'Z';
            } else if (r%9 == 4) {
                nextBlockType = 'T';
            } else if (r%9 == 5) {
                nextBlockType = 'L';
            } else if (r%9 == 6) {
                nextBlockType = 'J';
            } else if (r%9 == 7) {
                nextBlockType = 'I';
            } else {
                nextBlockType = 'O';
            }
        }
        // LEVEL 4
        if(level->getLevel() == 4) {
            if(r%9 <= 1) {
                nextBlockType = 'S';
            } else if (r%9 <= 3) {
                nextBlockType = 'Z';
            } else if (r%9 == 4) {
                nextBlockType = 'T';
            } else if (r%9 == 5) {
                nextBlockType = 'L';
            } else if (r%9 == 6) {
                nextBlockType = 'J';
            } else if (r%9 == 7) {
                nextBlockType = 'I';
            } else {
                nextBlockType = 'O';
            }
        }
    }
    return new Piece(static_cast<BlockType>(nextBlockType), 0, HEIGHT - 1, level->getLevel());
}
void PieceSequence::setFile(string filename){
    file = ifstream(filename);
} // sets the file stream
