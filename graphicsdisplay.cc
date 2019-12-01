//graphicsdisplay.cc
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include "graphicsdisplay.h"
using namespace std;



GraphicsDisplay::GraphicsDisplay(const vector<Board> &bs): xw {new Xwindow}, boards {{}} {
    for (int i = 0; i < bs.size(); ++i) {
        boards.emplace_back(&bs[i]);
    }
};

void GraphicsDisplay::drawBoards(std::ostream &out) {
    drawLevel(out);
    drawScore(out);
    drawHorizontalLine(out);
    drawGrid(out);
    drawHorizontalLine(out);
    drawNext(out);
}

void GraphicsDisplay::drawLevel(std::ostream &out) {
    string spaces;
    for (int i=0;i<=boards[0]->getWidth()-6;++i) {
	spaces += " ";
    }
    for (int i = 0; i < boards.size(); ++i) {
        string level; 
	istringstream iss {board[i]->getLevel()};
	iss >> level;
        if (i == 0) {
            xw->drawString(0,0, "Level:" + spaces + level);
	} else {
	    xw->drawString(i*boards[i].getWidth+8,0,"Level:" + spaces + level);
        }
    }
    out << endl;
}

void GraphicsDisplay::drawScore(std::ostream &out) {
    string spaces;
    for (int i=0;i<=boards[0].getWidth()-6;++i) {
	spaces += " ";
    }
    for (int i = 0; i < boards.size(); ++i) {
        string score; 
	istringstream iss {board[i]->getScore()};
	iss >> score;
        if (i == 0) {
            xw->drawString(0,1, "Level:" + spaces + score);
	} else {
	    xw->drawString(i*boards[i].getWidth+8,1,"Level:" + spaces + score);
        }
    }
    out << endl;
}

void GraphicsDisplay::drawHorizontalLine(std::ostream &out, size_t y) {
    string dashes;
    for (int i=0;i<=boards[0]->getWidth();++i) {
	dashes += " ";
    }
    for (int i = 0; i < boards.size(); ++i) {
        string score; 
	istringstream iss {board[i]->getScore()};
	iss >> score;
        if (i == 0) {
            xw->drawString(0,y,dashes);
	} else {
	    xw->drawString(i*boards[i].getWidth+8,y, dashes);
        }
    }
    out << endl;
}

// Will revise a bit later

void GraphicsDisplay::drawGrid(std::ostream &out) {
    // int boardHeight = boards[0].getHeight() + 3;
    // int boardWidth = boards[0].getWidth();

    // for (int y = boardHeight - 1; y >= 0; --y) {
    //     for (int i = 0; i < boards.size(); ++i) {
    //         if (i != 0) {
    //             out << setw(8);
    //         }
    //         Board board = boards[i];
    //         for (int x = 0; x < boardWidth; ++x) {
    //             if (board.getGrid()[boardHeight - y][x].getHasBlock()) {
    //                 out << board.getGrid()[y][x].getBlock().getSym();
    //             } else if (board.getCurPiece().hasCoord(make_pair(y, x))) {
    //                 out << board.getCurPiece().getSym();
    //             } else {
    //                 // change to space if this works
    //                 out << "*";
    //             }
    //         }
    //     }
    //     out << endl;
    // }
}

// Will revise a bit later

void GraphicsDisplay::drawNext(std::ostream &out) {
    // int boardHeight = boards[0].getHeight() + 3;
    // int boardWidth = boards[0].getWidth();

    // // Get height and width of the piececoord, then get the coordinate relatively
    // int maxHeight = 0;
    // for (int i = 0; i < boards.size(); ++i) {
    //     Board board = boards[i];
    //     maxHeight = max(maxHeight, board.getNextPiece().getHeight());
    // }
    // for (int y = 0; y < maxHeight; ++y) {
    //     for (int i = 0; i < boards.size(); ++i) {
    //         if (i != 0) {
    //             out << setw(8);
    //         }
    //         board = boards[i];
    //         int curPieceHeight = board.getNextPiece().getHeight();
    //         for (int x = 0; x < boardWidth; ++x) {
    //             if (board.getNextPiece().hasCoord(make_pair(curPieceHeight - 1 - y,x))) {
    //                 out << board.getCurPiece().getSym();
    //             } else {
    //                 // change to space if this works
    //                 out << "*";
    //             }
    //         }
    //     }
    //     out << endl;
    // }
}


// // // Print the 2D char array
// std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
//     drawBoards(out);
//     return out;
// }

