//textdisplay.cc
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include "textdisplay.h"
using namespace std;


TextDisplay::TextDisplay(vector<Board> &bs) {
    for (unsigned i = 0; i < bs.size(); ++i) {
        // boards is given as pointers since textdisplay will need to know everything about board
        //  every single time unlike graphics display
        boards.emplace_back(&bs[i]);
    }
    updateDisplay(cout); // initial display
};

void TextDisplay::updateDisplay(std::ostream &out) {
    // draw everything in order
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
            out << setw(13);
        }
        out << "Level:" << setw(boards[0]->getWidth()-6) << boards[i]->getLevel();
    }
    out << endl;
}

void TextDisplay::drawScore(std::ostream &out) {
    for (unsigned i = 0; i < boards.size(); ++i) {
        if (i != 0) {
            out << setw(13);
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
                    out << "?"; // blind
                } else if (board->getCurPiece()->hasCoord(make_pair(x, y))) {
                    out << board->getCurPiece()->getSym();  // check the coordinate of current piece, since it is not on grid yet
                } else if (y >= actualBoardHeight) {
                    out << " ";
                } else if (board->getGrid()[y][x].getHasBlock()) {
                    out << board->getGrid()[y][x].getBlock()->getSym();
                } else {
                    out << " ";
                }
            }
        }
        out << endl;
    }
}

void TextDisplay::drawNext(std::ostream &out) {
    int boardHeight = boards[0]->getHeight();
    int boardWidth = boards[0]->getWidth();

    for (unsigned i = 0; i < boards.size(); ++i) {
        if (i != 0) {
            out << setw(7+boardWidth);
        }
        out << "Next:";
    }
    out << endl;


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
            for (int x = 0; x < boardWidth; ++x) {
                // the coord in nextPiece is relative to the actual grid, so need boardHeight - y
                if (board->getNextPiece()->hasCoord(make_pair(x, boardHeight - 1 + y))) {
                    out << board->getNextPiece()->getSym();
                } else {
                    // change to space if this works
                    out << " ";
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
