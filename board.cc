#include "board.h"
#include "piececoords.h"

using namespace std;

bool Board::isRowFull(int r) { // returns if specified row is full
    bool full = true;
    for(int i = 0;i < WIDTH;++i) {
        if(!grid[r][i].getHasBlock()) {
            full = false;
        }
    }
    return full;
}

void Board::removeRowAndAddPoints(int r) { // MUST only be called if the row is full, always make sure row is full before calling this
    for(int i = 0;i < WIDTH;++i) {
        score += grid[r][i].removeBlockAndGetPoints();
    }
}

void Board::rotatePiece(bool clockwise) { // tries to rotate the piece, if it is not allowed we do not rotate it
    unique_ptr<PieceCoords> rpc = unique_ptr<PieceCoords>(curPiece->rotatePiece(clockwise)); // rotated piece coordinates
    if(!doesCollide(rpc.get())) { // if it doesn't collide, we set the coordinates
        curPiece->setCoords(rpc.get());
    } // otherwise do nothing
}

void Board::movePiece(int right, int down) { // tries to move the piece, if it is not allowed we do not move it
    unique_ptr<PieceCoords> rpc = unique_ptr<PieceCoords>(curPiece->movePiece(right, down)); // moved piece coordinates
    if(!doesCollide(rpc.get())) { // if it doesn't collide, we set the coordinates
        curPiece->setCoords(rpc.get());
    } // otherwise it does not get moved
}

// TODO: IMPLEMENT ALL THESE
    bool doesCollide(PieceCoords* pc);
    void removeFullRowsAndAddPoints();
    void getNextPiece(); // sets curPiece to nextPiece and gets the next piece
public:
    Board(std::string filename, int lvl = 0);
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
