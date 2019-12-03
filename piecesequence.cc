#include "piecesequence.h"
#include "block.h"
// #include <iostream>

using namespace std;

PieceSequence::PieceSequence(int lvl, bool hasSeed, int seed, int height): level{new Level{lvl}}, hasSeed{hasSeed}, seed{seed}, height{height} {
    this->random = level->isRandom(); // default value of random
    if(hasSeed){ // sets the seed if we have it
        srand(seed);
    } else {
        srand(time(NULL)); // sets the seed to null time by default
    }
}
PieceSequence::PieceSequence(std::string filename, int lvl, bool hasSeed, int seed, int height): filename{filename}, file{ifstream(filename)}, level{new Level{lvl}}, hasSeed{hasSeed}, seed{seed}, height{height} {
    this->random = level->isRandom();
    if(hasSeed){ // sets the seed if we have it
        srand(seed);
    } else {
        srand(time(NULL)); // sets the seed to null time by default
    }
}

Piece* PieceSequence::getPiece() { // generates a piece based on random and the Level and places it on the top left corner
    // all the probabilities are here
    char nextBlockType; // the next Piece type, it will create it based on a BlockType
    if(level->getLevel() == 0 || !random) { // it needs to be nonrandom here (level 0 has to be nonrandom)
        file >> nextBlockType;
        if(file.eof()) { // if we could not read the file (eof), then we restart the file stream
            file = ifstream(filename);
            file >> nextBlockType;
        }
        // cout << "Next Block Is: " << nextBlockType << endl;
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
    return new Piece(static_cast<BlockType>(nextBlockType), 0, height - 1, level->getLevel(), level->isHeavy());
}

void PieceSequence::setLevel(int lvl) { // sets the level and other stuff
    level->setLevel(lvl);
    random = level->isRandom();
}

void PieceSequence::setFile(string filename){
    this->filename = filename;
    this->file = ifstream(filename);
    this->random = false; // when we set a file, we just set random to false since we want to use the file now
} // sets the file stream

void PieceSequence::setRandom(bool random){
    this->random = random;
}
