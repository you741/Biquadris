//textdisplay.cc
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include "textdisplay.h"
using namespace std;


TextDisplay::TextDisplay(vector<Board> &bs) {
    for (unsigned i = 0; i < bs.size(); ++i) {
        boards.emplace_back(&bs[i]);
    }
};

void TextDisplay::drawBoards(std::ostream &out) {
    drawLevel(out);
    drawScore(out);
    drawHorizontalLine(out);
    drawGrid(out);
    drawHorizontalLine(out);
    drawNext(out);
}

void TextDisplay::drawLevel(std::ostream &out) {
    for (unsigned i = 0; i < boards.size(); ++i) {
        if (i != 0) {
            out << setw(8);
        }
        out << "Level:" << setw(boards[0]->getWidth()-6) << boards[i]->getLevel();
    }
    out << endl;
}

void TextDisplay::drawScore(std::ostream &out) {
    for (unsigned i = 0; i < boards.size(); ++i) {
        if (i != 0) {
            out << setw(8);
        }
        out << "Score:" << setw(boards[0]->getWidth()-6) << boards[i]->getScore();
    }
    out << endl;
}

void TextDisplay::drawHorizontalLine(std::ostream &out) {
    for (unsigned i = 0; i < boards.size(); ++i) {
        if (i != 0) {
            out << setw(8);
        }
        for (int j=0;j<boards[0]->getWidth();++j) {
	    out << "-";
	}
    }
    out << endl;
}

void TextDisplay::drawGrid(std::ostream &out) {
    int actualBoardHeight = boards[0]->getHeight();
    int boardHeight = actualBoardHeight + 3;
    int boardWidth = boards[0]->getWidth();

    for (int y = boardHeight - 1; y >= 0; --y) {
        for (unsigned i = 0; i < boards.size(); ++i) {
            if (i != 0) {
                out << setw(8);
            }
            Board *board = boards[i];
            bool blind = board->getBlind();
            for (int x = 0; x < boardWidth; ++x) {
                if (blind && ((2 <= x && x <= 8) || (2 <= y && y <= 11))) {
                    out << "?";
                } else if (board->getCurPiece()->hasCoord(make_pair(y, x))) {
                    out << board->getCurPiece()->getSym();
                } else if (y >= actualBoardHeight) {
                    out << "*";
                } else if (board->getGrid()[y][x].getHasBlock()) {
                    out << board->getGrid()[y][x].getBlock()->getSym();
                } else {
                    // change to space if this works
                    out << "*";
                }
            }
        }
        out << endl;
    }
}

void TextDisplay::drawNext(std::ostream &out) {
    int boardHeight = boards[0]->getHeight() + 3;
    int boardWidth = boards[0]->getWidth();

    // Get height and width of the piececoord, then get the coordinate relatively
    int maxHeight = 0;
    for (unsigned i = 0; i < boards.size(); ++i) {
        Board *board = boards[i];
        maxHeight = max(maxHeight, board->getNextPiece()->getHeight());
    }
    for (int y = maxHeight - 1; y >= 0; --y) {
        for (unsigned i = 0; i < boards.size(); ++i) {
            if (i != 0) {
                out << setw(8);
            }
            Board *board = boards[i];
            int curPieceHeight = board->getNextPiece()->getHeight();
            for (int x = 0; x < boardWidth; ++x) {
                if (board->getNextPiece()->hasCoord(make_pair(curPieceHeight - 1 - y,x))) {
                    out << board->getCurPiece()->getSym();
                } else {
                    // change to space if this works
                    out << "*";
                }
            }
        }
        out << endl;
    }
}


// // Draw the board
// std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
//     this->drawBoards(out);
//     return out;
// }
