#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include "boardinfo.h"
#include "command.h"
#include "cell.h"
#include "piecesequence.h"
#include "piececoords.h"
#include "piece.h"
#include "window.h"

const int MAX_LEVEL = 4; // max level

class Board {
    int lastCleared = 0; // the last turn a row was cleared
    int turn = 0; // the turn of the board. goes up by one every drop
    std::unique_ptr<Level> level;
    std::string file0; // the sequence of blocks for level 0
    std::unique_ptr<PieceSequence> seq; // the seq will let us generate next pieces
    std::unique_ptr<Piece> curPiece;
    std::unique_ptr<Piece> nextPiece;
    std::vector<std::vector<Cell>> grid;
    bool heavy = false;
    bool specialHeavy = false; // special heavy is a little different than normal heavy
    bool splitBlock = false; // the splitting block shows up in level 4
    bool blind = false;
    bool special = false; // if 2+ rows were cleared, we set this to true so Game can tell it needs a special effect
    bool lost = false; // did they lose the game
    int score = 0;
    int width = 11;
    int height = 15;
    bool isRowFull(int r);
    void removeRowAndAddPoints(int r);
    bool rotatePiece(bool clockwise = true);
    bool movePiece(int right = 0, int down = 0);
    void heavyFall(); // handles heavy effects
    void specialHeavyFall();
    bool doesCollide(PieceCoords* pc);
    void removeFullRowsAndAddPoints();
    void setNextPiece(); // sets curPiece to nextPiece and gets the next piece
    void drop(); // drops the piece
public:
    Board(bool hasSeed, int seed, std::string file0, int lvl = 0);
    void applyCommand(const Command &c);
    void setLevel(int lvl);
    // getters
    int getTurn() const;
    Piece* getCurPiece() const;
    Piece* getNextPiece() const;
    const std::vector<std::vector<Cell>> &getGrid() const;
    bool getHeavy() const;
    bool getBlind() const;
    int getLevel() const; // returns level number rather than whole level class, this is enough information for Game
    bool getSpecial() const;
    bool getLost() const;
    int getScore() const;
    int getWidth() const;
    int getHeight() const;
    BoardInfo getInfo() const;
    // TODO: need to make attach later

    //setters
    void setSpecial(bool special);
};
#endif // BOARD_H
