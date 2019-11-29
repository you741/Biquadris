//textdisplay.cc
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include "subject.h"
#include "textdisplay.h"
using namespace std;


TextDisplay::TextDisplay(vector<Board> bs): {
    for (int i = 0; i < bs.size(); ++i) {
        boards.emplace_back(&bs[i]);
    }
};

// When a cell is changed, draw the TextDisplay
void TextDisplay::notify(Subject<BoardInfo, BoardState> &whoNotified) {
	drawBoards(cout);
}

void TextDisplay::drawBoards(std::ostream &out) {
    drawLevel(out);
    drawScore(out);
    drawGrid(out);
    drawNext(out);
}

void TextDisplay::drawLevel(std::ostream &out) {
    for (int i = 0; i < boards.size(); ++i) {
        if (i != 0) {
            cout << setw(8);
        }
        board = boards[i];
        cout << "Level:" << setw(w-6) << board->getLevel();
    }
    cout << endl;
}

void TextDisplay::drawScore(std::ostream &out) {
    for (int i = 0; i < boards.size(); ++i) {
        if (i != 0) {
            cout << setw(8);
        }
        board = boards[i];
        cout << "Score:" << setw(w-6) << board->getScore();
    }
    cout << endl;
}

void TextDisplay::drawGrid(std::ostream &out) {
    int boardHeight = boards[0].getHeight() + 3;
    int boardWidth = boards[0].getWidth();

    for (int y = boardHeight - 1; y >= 0; --y) {
        for (int i = 0; i < boards.size(); ++i) {
            if (i != 0) {
                cout << setw(8);
            }
            board = boards[i];
            for (int x = 0; x < boardWidth; ++x) {
                if (board.getGrid()[boardHeight - y][x].getHasBlock()) {
                    cout << board.getGrid()[y][x].getBlock().getSym();
                } else if (board.getCurPiece().hasCoord(make_pair(y, x))) {
                    cout << board.getCurPiece().getSym();
                } else {
                    // change to space if this works
                    cout << "-";
                }
            }
        }
        cout << endl;
    }
}

void TextDisplay::drawNext(std::ostream &out) {
    int boardHeight = boards[0].getHeight() + 3;
    int boardWidth = boards[0].getWidth();

    // Get height and width of the piececoord, then get the coordinate relatively
    int maxHeight = 0;
    for (int i = 0; i < boards.size(); ++i) {
        board = boards[i];
        maxHeight = max(maxHeight, board.getCurPiece().getHeight());
    }
    for (int y = 0; y < maxHeight; ++y) {
        for (int i = 0; i < boards.size(); ++i) {
            if (i != 0) {
                cout << setw(8);
            }
            board = boards[i];
            int curPieceHeight = board.getCurPiece().getHeight();
            for (int x = 0; x < boardWidth; ++x) {
                if (board.getCurPiece().hasCoord(make_pair(curPieceHeight - 1 - y,x))) {
                    cout << board.getCurPiece().getSym();
                } else {
                    // change to space if this works
                    cout << "-";
                }
            }
        }
        cout << endl;
    }
}


// // Print the 2D char array
// std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
// 	drawBoards(out);
// 	return out;
// }
