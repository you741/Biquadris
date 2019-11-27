#include <utility>
#include "rotate.h"
#include "piece.h"

using namespace std;

RotateCommand::RotateCommand(bool clockwise): Command{}, clockwise{clockwise} {}

void RotateCommand::apply(Board *b) {
    const Piece &p = b->getCurPiece();
    const PieceCoords &pc = p->getPieceCoords();
    int newHeight = pc->getWidth();
    int newWidth = pc->getHeight();
    int leftmost = pc->getLeftMost();
    int lowest = pc->getLowest();
    vector<pair<int,int>> newBlocks;
    if(clockwise) {
        for(const auto &p: pc->getBlocks()) { // goes through every block and alters its x and y coordinates to rotate it clockwise
            int newX = leftmost + (p.second - lowest); // new X is based on old y and vice versa, we work with everything relative to bottom-left
            int newY = lowest + newHeight - (p.first - leftmost);
            newBlocks.emplace_back(make_pair(newX,newY));
        }
    } else {
        for(const auto &p: pc->getBlocks()) { // goes through every block and alters its x and y coordinates to rotate it counterclockwise
            int newX = leftmost + (lowest + pc->getHeight() - p.second);
            int newY = lowest + (p.first - leftmost);
            newBlocks.emplace_back(make_pair(newX,newY));
        }
    }
    PieceCoords npc = PieceCoords(newBlocks);
    if (!b->doesCollide(npc)) {
        b->setPieceCoords(npc);
    } // only change the piece's coordinates if it does not collide, otherwise we don't change the state to avoid collisions
}
