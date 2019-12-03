//graphicsdisplay.cc
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include "graphicsdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(vector<Board> &bs) {
    for (int i=0; i<bs.size(); ++i) {
        boards.emplace_back(&bs[i]);
        xw.emplace_back(new Xwindow);
        init(i);
    }
};

GraphicsDisplay::~GraphicsDisplay() {
    for (int i=0;i<xw.size(); ++i){
        delete xw[i];
    }
}

void GraphicsDisplay::init(int id) {
    ostringstream oss;
    oss << id+1;
    xw[id]->drawString(leftIndent, topIndent, "Player"+oss.str(), Xwindow::Black);
    xw[id]->drawString(leftIndent, topIndent+lineBreak, "Level:");
    xw[id]->drawString(leftIndent, topIndent+lineBreak*2, "Score:");
    for (int y=topIndent+lineBreak*3; y<=topIndent+lineBreak*3+cellWidth*boardHeight; y+=cellWidth) {
	xw[id]->drawLine(leftIndent, y, leftIndent+cellWidth*boardWidth, y);
    }
    for (int x=leftIndent; x<=leftIndent+cellWidth*boardWidth; x+=cellWidth) {
	xw[id]->drawLine(x, topIndent+lineBreak*3, x, topIndent+lineBreak*3+cellWidth*boardHeight);
    }
    xw[id]->drawString(leftIndent, topIndent+lineBreak*4.5+cellWidth*boardHeight, "Next:");
}

void GraphicsDisplay::updateDisplay(int id) {
    updateLevel(id);
    updateScore(id);
    updateGrid(id);
    updateNext(id);
}

void GraphicsDisplay::updateLevel(int id) {
    ostringstream oss;
    oss << boards[id]->getScore();
    xw[id]->fillRectangle(leftIndent+slIndent, topIndent+lineBreak, slIndent, lineBreak, 0); // clean the previous level
    xw[id]->drawString(leftIndent+slIndent, topIndent+lineBreak*2, oss.str());
}

void GraphicsDisplay::updateScore(int id) {
    ostringstream oss;
    oss << boards[id]->getLevel();
    xw[id]->fillRectangle(leftIndent+slIndent, topIndent, slIndent, lineBreak, 0); // clean the previous score
    xw[id]->drawString(leftIndent+slIndent, topIndent+lineBreak, oss.str());
}

void GraphicsDisplay::updateGrid(int id) {
    int fullHeight = boards[0]->getHeight()+3;
    bool blind = boards[id]->getBlind();
    for (int y=fullHeight-1; y>=0; --y) {
        for (int x=0; x<boards[id]->getWidth(); ++x) {
            if (blind && ((2 <= x && x <= 8) || (2 <= y && y <= 11))) {
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1, topIndent+lineBreak*3+cellWidth*(fullHeight-1-y)+1,
                        cellWidth-2,cellWidth-2, 1); // +2 and -2 are to prevent overwriting the lines drawn
            } else if (boards[id]->getCurPiece()->hasCoord(make_pair(x,y))) {
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1, topIndent+lineBreak*3+cellWidth*(fullHeight-1-y)+1,
                       cellWidth-2, cellWidth-2, boards[id]->getCurPiece()->getColour());
                        // +2 and -2 are to prevent overwriting the line drawn
            } else if (y > fullHeight - 4) {
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1, topIndent+lineBreak*3+cellWidth*(fullHeight-1-y)+1,
                        cellWidth-2,cellWidth-2, 0); // +2 and -2 are to prevent overwriting the lines drawn
            } else if (boards[id]->getGrid()[y][x].getHasBlock()) {
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1, topIndent+lineBreak*3+cellWidth*(fullHeight-1-y)+1,
                       cellWidth-2, cellWidth-2, boards[id]->getGrid()[y][x].getBlock()->getColour());
                        // +2 and -2 are to prevent overwriting the line drawn
            } else {
                xw[id]->fillRectangle(leftIndent+x*cellWidth+1, topIndent+lineBreak*3+cellWidth*(fullHeight-1-y)+1,
                        cellWidth-2,cellWidth-2, 0); // +2 and -2 are to prevent overwriting the lines drawn
            }
        }
    }
}

void GraphicsDisplay::updateNext(int id){
    xw[id]->fillRectangle(leftIndent, topIndent+lineBreak*4.5+cellWidth*boardHeight, slIndent*4, lineBreak*5, 0); // clean the previous next_block
    for (auto block : boards[id]->getNextPiece()->getBlocks()) {
           xw[id]->fillRectangle(leftIndent+(block.first)*cellWidth, topIndent+lineBreak*5+cellWidth*boardHeight+(boards[0]->getHeight()-block.second)*cellWidth,
                    cellWidth, cellWidth, boards[id]->getNextPiece()->getColour());
    }
}
