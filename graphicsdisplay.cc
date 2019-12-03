//graphicsdisplay.cc
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include "graphicsdisplay.h"
#include "cell.h"


using namespace std;

GraphicsDisplay::GraphicsDisplay(vector<Board> &bs) {
    for (unsigned i=0; i<bs.size(); ++i) {
        // boards.emplace_back(&bs[i]);
        xw.emplace_back(make_unique<Xwindow>());

        vector <vector <int>> tmpState;
        for(int j = 0; j < bs[i].getHeight() + 3;++j){ // adds rows of cells equal to the height
            tmpState.emplace_back(vector<int>(bs[i].getWidth(), Xwindow::White));
        }
        state.emplace_back(tmpState);

        init(i); //draw the initial state
    }
};

void GraphicsDisplay::init(int id) {
    ostringstream oss;
    oss << id+1;
    xw[id]->drawString(leftIndent, topIndent, "Player "+oss.str(), Xwindow::Black);
    xw[id]->drawString(leftIndent, topIndent+lineBreak, "Level:");
    xw[id]->drawString(leftIndent, topIndent+lineBreak*2, "Score:");
    xw[id]->drawString(leftIndent, topIndent+lineBreak*4.5+cellWidth*boardHeight, "Next:");
    drawGrid(id);
    // only get drawn once per board
}

void GraphicsDisplay::setState(int id, const vector<vector<Cell>> &grid, Piece *piece, bool blind, int width, int height) {
    int fullHeight = height+3;

    // used oldState to compare changes
    oldState = state;

    for (int y=fullHeight-1; y>=0; --y) {
        for (int x=0; x<width; ++x) {
            if (blind && ((2 <= x && x <= 8) || (2 <= y && y <= 11))) {
                state[id][y][x] = Xwindow::Black;   //blind
            } else if (piece->hasCoord(make_pair(x,y))) {
                state[id][y][x] = piece->getColour();   //current piece coordinate
            } else if (y > fullHeight - 4) {
                state[id][y][x] = Xwindow::White;   //above the actual board, defaults to white
            } else if (grid[y][x].getHasBlock()) {
                state[id][y][x] = grid[y][x].getBlock()->getColour(); //normal block that has been placed
            } else {
                state[id][y][x] = Xwindow::White;
            }
        }
    }
}

// draw the grid lines
void GraphicsDisplay::drawGrid(int id) {
    xw[id]->fillRectangle(leftIndent, topIndent+lineBreak*3, cellWidth*boardWidth, cellWidth*boardHeight, 0); // clean the previous level
    for (int y=topIndent+lineBreak*3; y<=topIndent+lineBreak*3+cellWidth*boardHeight; y+=cellWidth) {
	    xw[id]->drawLine(leftIndent, y, leftIndent+cellWidth*boardWidth, y);
    }
    for (int x=leftIndent; x<=leftIndent+cellWidth*boardWidth; x+=cellWidth) {
	    xw[id]->drawLine(x, topIndent+lineBreak*3, x, topIndent+lineBreak*3+cellWidth*boardHeight);
    }
}

void GraphicsDisplay::updateScore(int id, int score) {
    ostringstream oss;
    oss << score;
    xw[id]->fillRectangle(leftIndent+slIndent, topIndent+lineBreak, slIndent, lineBreak, 0); // clean the previous score
    xw[id]->drawString(leftIndent+slIndent, topIndent+lineBreak*2, oss.str());
}

void GraphicsDisplay::updateLevel(int id, int level) {
    ostringstream oss;
    oss << level;
    xw[id]->fillRectangle(leftIndent+slIndent, topIndent, slIndent, lineBreak, 0); // clean the previous level
    xw[id]->drawString(leftIndent+slIndent, topIndent+lineBreak, oss.str());
}

void GraphicsDisplay::updateGrid(int id, int width, int height) {
    int fullHeight = height+3;
    for (int y=fullHeight-1; y>=0; --y) {
        for (int x=0; x<width; ++x) {
            // only draw if the board has changed or first time drawing
            if (oldState.size() == 0 || state[id][y][x] != oldState[id][y][x]) {
                int colour = state[id][y][x];
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1, topIndent+lineBreak*3+cellWidth*(fullHeight-1-y)+1,
                        cellWidth-1,cellWidth-1, colour); // +1 and -1 are to prevent overwriting the lines drawn
            }
        }
    }
}

void GraphicsDisplay::updateNext(int id, Piece *nextPiece, int height){
    xw[id]->fillRectangle(leftIndent, topIndent+lineBreak*4.5+cellWidth*boardHeight, slIndent*4, lineBreak*5, 0); // clean the previous next_block
    for (auto block : nextPiece->getBlocks()) {
           xw[id]->fillRectangle(leftIndent+(block.first)*cellWidth, topIndent+lineBreak*5+cellWidth*boardHeight+(height-block.second)*cellWidth,
                    cellWidth, cellWidth, nextPiece->getColour());
    }
}


void GraphicsDisplay::notify(Subject<BoardInfo, BoardState> &whoFrom) {
	// get the state information about what is notifying
	BoardState state = whoFrom.getState();
	BoardInfo info = whoFrom.getInfo();

    //update specific things based on what changed
	if (state.type == StateType::BoardChange) {
        updateLevel(info.id, info.level);
        updateScore(info.id, info.score);
        setState(info.id, info.grid, info.piece, info.blind, info.width, info.height);
        updateGrid(info.id, info.width, info.height);
        updateNext(info.id, info.nextPiece, info.height);
	} else if (state.type == StateType::LevelChange) {
        updateLevel(info.id, info.level);
	}  else if (state.type == StateType::ScoreChange) {
        updateScore(info.id, info.score);
	} else if (state.type == StateType::BlindChange) {
        setState(info.id, info.grid, info.piece, info.blind, info.width, info.height);
        updateGrid(info.id, info.width, info.height);
	} else if (state.type == StateType::PieceMoved) {
		setState(info.id, info.grid, info.piece, info.blind, info.width, info.height);
        updateGrid(info.id, info.width, info.height);
	} else if (state.type == StateType::PieceDropped) {
		updateLevel(info.id, info.level);
        updateScore(info.id, info.score);
        setState(info.id, info.grid, info.piece, info.blind, info.width, info.height);
        updateGrid(info.id, info.width, info.height);
        updateNext(info.id, info.nextPiece, info.height);
	} else if (state.type == StateType::NextPiece) {
        updateNext(info.id, info.nextPiece, info.height);
	}
}
