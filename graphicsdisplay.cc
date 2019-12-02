//graphicsdisplay.cc
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include "graphicsdisplay.h"
using namespace std;

size_t getIndex(const Vector<char> &v, char &c) {
    for (size_t i=0; i<v.size(); ++i) {
        if (v[i] == c) {
            return i;
        }
    }
    return 0;
}

GraphicsDisplay::GraphicsDisplay(const vector<Board> &bs): boards {{}}, xw {{}} {
    for (size_t i=0; i<bs.size(); ++i) {
        boards.emplace_back(&bs[i]);
        xw.emplace_back(new Xwindow);
        init(i);
    }
};

GraphicsDisplay::~GraphicsDisplay() {
    for (size_t i=0;i<xw.size(); ++i){
        delete xw[i];
    }
}

void GraphicsDisplay::init(size_t id) {
    ostringstream oss {id};
    xw[id]->drawString(leftIndent, topIndent,"Player"+oss.str());
	xw[id]->drawString(leftIndent, topIndent+lineBreak, "Level:");
	xw[id]->drawString(leftIndent, topIndent+lineBreak*2, "Score:");
	for (size_t y=topIndent+lineBreak*3; y<=topIndent+lineBreak*3+cellWidth*boardHeight; y+=cellWidth) {
	    xw[id]->drawLine(leftIndent, y, leftIndent+cellWidth*boardWidth, y);
	}
    for (size_t x=leftIndent; x<=leftIndent+cellWidth*boardWidth; x+=cellWidth) {
	    xw[id]->drawLine(x, topIndent+lineBreak*3, x, topIndent+lineBreak*3+cellWidth*boardHeight);
	}
    xw[id]->drawString(leftIndent, topIndent+lineBreak*4.5+cellWidth*boardHeight, "Next:");
}

void GraphicsDisplay::updateDisplay(size_t id) {
    updateLevel(id);
    updateScore(id);
    updateGrid(id);
    updateNext(id);
}

void GraphicsDisplay::updateLevel(size_t id) {
    ostringstream oss {boards[id]->getScore()};
    xw[id]->fillRectangle(leftIndent+slIndent, topIndent+lineBreak, slIndent, lineBreak, 0); // clean the previous level
    xw[id]->drawString(leftIndent+slIndent, topIndent+lineBreak*2, oss.str());
}

void GraphicsDisplay::updateScore(size_t id) {
    ostringstream oss {boards[id]->getLevel()};
    xw[id]->fillRectangle(leftIndent+slIndent, topIndent, slIndent, lineBreak, 0); // clean the previous score
    xw[id]->drawString(leftIndent+slIndent, topIndent+lineBreak, oss.str());
}

void GraphicsDisplay::updateGrid(size_t id) {
    for (size_t y=boardHeight-1; y>=0; --y) {
        for (size_t x=0; x<boardWidth; ++x) {
            if (boards[id]->getGrid()[boardHeight-y][x].getHasBlock()) {
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1,topIndent+lineBreak*3+cellWidth*y,
                        cellWidth-1,cellWidth-1, getIndex(colours, boards[id]->getCurPiece().getSym()));
                        // +1 and -1 are to prevent overwriting the line drawn
            } else if (boards[id]->getCurPiece().hasCoord(make_pair(y,x))) {
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1,topIndent+lineBreak*3+cellWidth*y,
                        cellWidth-1,cellWidth-1, getIndex(colours, boards[id]->getCurPiece().getSym()));
                        // +1 and -1 are to prevent overwriting the line drawn
            } else {
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1,topIndent+lineBreak*3+cellWidth*y,
                        cellWidth-1,cellWidth-1, 0); // +1 and -1 are to prevent overwriting the lines drawn
            }
        }
    }
}

void GraphicsDisplay::updateNext(size_t id){
    xw->fillRectangle(leftIndent, topIndent+lineBreak*4.5+cellWidth*boardHeight, slIndent, lineBreak*3, 0); // clean the previous next_block
    for (auto block : boards[id]->getNextPiece().getBlocks()) {
           xw[id]->fillRectangle(leftIndent+(block->first)*cellWidth, topIndent+lineBreak*5.5+(block->second)*cellWidth,
                    cellWidth, cellWidth, getIndex(colours, boards[id]->getNextPiece().getSym());
    }
}
