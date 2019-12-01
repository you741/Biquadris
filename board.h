#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include <string>
#include "boardinfo.h"
#include "command.h"
#include "cell.h"
#include "piecesequence.h"
#include "piececoords.h"

const int WIDTH = 11; // height and width of the board, they are global
const int HEIGHT = 15;

class Board {
    int lastCleared = 0; // the last turn a row was cleared
    int turn = 0; // the turn of the board. goes up by one every drop
    std::unique_ptr<Piece> curPiece;
    std::unique_ptr<Piece> nextPiece;
    std::vector<std::vector<Cell>> grid;
    std::unique_ptr<PieceSequence> seq; // the seq will let us generate next pieces
    bool heavy = false;
    bool blind = false;
    std::unique_ptr<Level> level;
    bool special = false; // if 2+ rows were cleared, we set this to true so Game can tell it needs a special effect
    bool lost = false; // did they lose the game
    int score = 0;

    bool isRowFull(int r);
    void removeRowAndAddPoints(int r);
    void rotatePiece(bool clockwise = true);
    void movePiece(int right = 0, int down = 0);
    bool doesCollide(PieceCoords* pc);
    void removeFullRowsAndAddPoints();
    void getNextPiece(); // sets curPiece to nextPiece and gets the next piece
public:
    Board(bool hasSeed, int seed, std::string filename, int lvl = 0);
    void applyCommand(Command c);
    void setLevel(int lvl);
    // getters
    int getTurn() const;
    Piece* getCurPiece() const;
    Piece* getNextPiece() const;
    std::vector<std::vector<Cell>> &getGrid() const;
    bool getHeavy() const;
    bool getBlind() const;
    int getLevel() const; // returns level number rather than whole level class, this is enough information for Game
    bool getSpecial() const;
    bool getLost() const;
    int getScore() const;
    BoardInfo getInfo() const;
    // TODO: need to make attach later

    //setters
    void setCurPiece(Piece *p);
    void setSpecial(bool special);
};
#endif // BOARD_H
