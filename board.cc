#include "board.h"
#include "piececoords.h"

using namespace std;

bool Board::isRowFull(int r) { // returns if specified row is full
    bool full = true;
    for(int i = 0;i < width;++i) {
        if(!grid[r][i].getHasBlock()) {
            full = false;
        }
    }
    return full;
}

void Board::removeRowAndAddPoints(int r) { // MUST only be called if the row is full, always make sure row is full before calling this
    for(int i = 0;i < width;++i) {
        score += grid[r][i].removeBlockAndGetPoints();
    }
}

bool Board::rotatePiece(bool clockwise) { // tries to rotate the piece, if it is not allowed we do not rotate it
    unique_ptr<PieceCoords> rpc(curPiece->rotatePiece(clockwise)); // rotated piece coordinates
    if(!doesCollide(rpc.get())) { // if it doesn't collide, we set the coordinates
        curPiece->setCoords(move(rpc));
        return true; // successful rotate
    } // otherwise do nothing
    return false; // failed rotate
}

bool Board::movePiece(int right, int down) { // tries to move the piece, if it is not allowed we do not move it
    unique_ptr<PieceCoords> mpc(curPiece->movePiece(right, down)); // moved piece coordinates
    if(!doesCollide(mpc.get())) { // if it doesn't collide, we set the coordinates
        curPiece->setCoords(move(mpc));
        return true; // successful move
    } // otherwise do nothing
    return false; // failed move
}

void Board::heavyFall() { // handles the heavy effect, if there is one
    if(curPiece->isHeavy()) { // if it is a heavy piece try to move down onei
        movePiece(0,1);
    }
}

void Board::specialHeavyFall() { // handles falling by special heavy effect
    if(specialHeavy) { // tries to move down by 2, runs a Drop command if we can't
        if(!movePiece(0,2)) { // if we didn't succeed in moving, we apply drop
            applyCommand(Command(CommandType::Drop));
        }
    }
}

bool Board::doesCollide(PieceCoords* pc, bool checkUpperBound) {
    for(const auto &p: pc->getBlocks()) {
        if(p.second < 0 || p.first < 0 || p.first >= width || (p.second >= height && checkUpperBound)) { // if the coordinate is out of bounds, return true
            return true;
        } else if (p.second < height && grid[p.second][p.first].getHasBlock()) { // if the coordinate is on a block, it is also true (it does collide)
            return true;
        }
    }
    return false; // does not collide
}

void Board::removeFullRowsAndAddPoints() { // checks every row, if it is full we remove it and add the points to score
    bool fullRows = true; // assume there might be some full rows at the beginning, this is true if there are fullRows in the grid
    int numFullRows = 0; // if there are more than 1 full rows, we can activate a special effect
    while(fullRows) { // keep removing full rows until there are none
        fullRows = false; // assume it's false now
        for(int i = height - 1;i >= 0;--i) { // start at the top so we can remove and replace no problem
            if(isRowFull(i)) { // if the row is full, remove the row and add points
                removeRowAndAddPoints(i);
                grid.erase(grid.begin() + i); // deletes the row at i
                grid.emplace_back(vector<Cell>(width,Cell{})); // inserts a new row of empty cells at the end
                fullRows = true; // we found a full row
                numFullRows++;
            }
        }
    }
    if(numFullRows >= 2) { // if we cleared at least 2 rows, we can prompt for a special action
        special = true;
    }
    if(numFullRows >= 1) { // if we cleared at least row, we reset the turn we last cleared a block (relevant for levels with splitting blocks)
        lastCleared = turn;
	score += (numFullRows + level->getLevel()) * (numFullRows + level->getLevel());
    }
}

void Board::setNextPiece() { // sets curPiece to nextPiece and gets the next piece
    curPiece = move(nextPiece); // transfers ownership of the nextPiece to the current piece
    nextPiece = unique_ptr<Piece>(seq->getPiece()); // sets the next piece
    if(doesCollide(curPiece->getCoords())) {
        lost = true; // if our new piece collides, we lost
    }
}

void Board::drop() { // drops the piece to the lowest possible point
    while(true){ // moves down as much as possible
        bool moved = movePiece(0,1);
        if(!moved) {
            break;
        }
    }
    if(doesCollide(curPiece->getCoords(),true)) {
	cout << "lost" << endl;
        lost = true; // we lose if we dropped the piece off the board
        return;
    }
    vector<Block*> newBlocks = curPiece->makeBlocks();
    for(size_t i = 0;i < newBlocks.size();++i) { // moves the actual blocks on the board
        grid[newBlocks[i]->getRow()][newBlocks[i]->getCol()].setBlock(newBlocks[i]);
    }
    turn++; // turn goes up by one
    removeFullRowsAndAddPoints(); // removes all full rows and adds points
    setNextPiece(); // sets the nextPiece
}

Board::Board(bool hasSeed, int seed, string file0, int id, int lvl): level{make_unique<Level>(lvl)}, file0{file0}, id{id} {
    // we set our sequence
    if(lvl == 0) { // level 0 needs to start with a sequence, so we create piece sequence with a file
        seq = make_unique<PieceSequence>(file0,lvl,hasSeed,seed,height);
    } else { // otherwise we do not need to specify a file right away
        seq = make_unique<PieceSequence>(lvl,hasSeed,seed,height);
    }
    curPiece = unique_ptr<Piece>(seq->getPiece()); // sets the pieces
    nextPiece = unique_ptr<Piece>(seq->getPiece());
    for(int i = 0;i < height;++i){ // adds rows of cells equal to the height
        grid.emplace_back(vector<Cell>(width,Cell{}));
    }
    heavy = level->isHeavy();
    splitBlock = level->hasSplitBlock();

}

void Board::initNotify() {
    setState(BoardState{StateType::BoardChange});
    notifyObservers();
}

void Board::applyCommand(const Command &c) { // applies the command
    if(c.commandType == CommandType::MoveLeft) { // move left
        for(int i = 0;i < c.rep;++i) {// moves piece rep times to the left
            if (!movePiece(-1,0)) break; // breaks on failed move to save time
        }
        heavyFall();
        specialHeavyFall();
        setState(BoardState{StateType::PieceMoved});
    } else if (c.commandType == CommandType::MoveRight) { // move right
        for(int i = 0;i < c.rep;++i) {// moves piece rep times to the right
            if (!movePiece(1,0)) break; // breaks on failed move to save time
        }
        heavyFall();
        specialHeavyFall();
        setState(BoardState{StateType::PieceMoved});
    } else if (c.commandType == CommandType::MoveDown) { // move down
        for(int i = 0;i < c.rep;++i) {// moves piece rep times to the down
            if (!movePiece(0,1)) break; // breaks on failed move to save time
        }
        heavyFall();
        setState(BoardState{StateType::PieceMoved});
    } else if (c.commandType == CommandType::Clockwise) { // rotates clockwise
        // cout << "Lowest is: " << curPiece->getLowest() << endl;
        // cout << "LeftMost is: " << curPiece->getLeftmost() << endl;
        for(int i = 0;i < c.rep%4;++i) { // repeats by modulo 4 because every 4 rotations is the same
            if(!rotatePiece()) break;
        }
        heavyFall();
        setState(BoardState{StateType::PieceMoved});
    } else if (c.commandType == CommandType::CounterClockwise) {
        for(int i = 0;i < c.rep%4;++i) {
            if(!rotatePiece(false)) break;
        }
        heavyFall();
        setState(BoardState{StateType::PieceMoved});
    } else if (c.commandType == CommandType::LevelUp) { // moves level up
        setLevel(min(MAX_LEVEL,level->getLevel() + c.rep)); // increases level by rep amount
        setState(BoardState{StateType::LevelChange});
    } else if (c.commandType == CommandType::LevelDown) {
        setLevel(max(0, level->getLevel() - c.rep));
        setState(BoardState{StateType::LevelChange});
    } else if (c.commandType == CommandType::NoRandom) {
        if(level->getLevel() == 3 || level->getLevel() == 4) {
            // needs to be level 3 or 4 to remove the random
            seq->setFile(c.file);
        }
    } else if (c.commandType == CommandType::Random) {
        if(level->getLevel() == 3 || level->getLevel() == 4) {
            // needs to be level 3 or 4 to add the random
            seq->setRandom(true);
        }
    } else if (c.commandType == CommandType::Sequence) {
        // handled in Game, should do nothing here
    } else if (c.commandType == CommandType::Restart) {
	// Game handles this
    } else if (c.commandType == CommandType::Heavy) {
        specialHeavy = true;
    } else if (c.commandType == CommandType::Force) { // sets a new piece, could lose
        curPiece.reset(new Piece(c.b, 0, height - 1, level->getLevel(),heavy)); // gets rid of current piece for a new one
        if(doesCollide(curPiece->getCoords())) {
            lost = true; // we lose if we can't change the piece
        }
        
    } else if (c.commandType == CommandType::Blind) {
        blind = true;
    } else if (c.commandType == CommandType::ChangePiece) {
        unique_ptr<Piece> newPiece(new Piece(c.b, 0, height - 1, level->getLevel(), heavy));
        if(!doesCollide(newPiece->getCoords())) {
            // if it doesn't collide we transfer ownership to our curPiece
            curPiece = move(newPiece);
        }
        setState(BoardState{StateType::PieceMoved});
    } else if (c.commandType == CommandType::EndOfFile) {
        // do nothing, Game handles this
    } else if (c.commandType == CommandType::Drop) {
        special = false; // we never get a special action unless we clear at least 2 rows, if we do the Drop command should set it to true
        dropped = true;
        blind = false;
        for(int i = 0;i < c.rep && !lost;++i){
	    drop(); // drops piece to the bottom, removes all full rows, moves turn up by 1
            if(lost) break; // no need to continue if we lost
            if(splitBlock) {
                if(turn - lastCleared > 0 && (turn - lastCleared)%5 == 0) {
                    // if it is a multiple of 5th turn since we last cleared a row, we may have to place a split block
                    if(grid[height - 1][int(width/2)].getHasBlock()) { // if we have a block at the top of the middle row, we lose
                        lost = true;
                        break;
                    }
                    int j = height - 1;
                    for(j = height - 1;j >= 0;--j) {
                        // tries the middle of the grid and tries place a block there start at the bottom
                        if(grid[j][int(width/2)].getHasBlock()) {
                            // if we find one with block, we stop here and place the block at row j+1 to put it right above here
                            ++j;
                            break;
                        }
                    }
                    if(j == -1) j = 0; // if we reached the end with no breaks, j ends up as -1. we set it to 0 in this case.
                    grid[j][int(width/2)].setBlock(new Block(make_pair(int(width/2),j),0,Xwindow::Brown,'*')); // drops the split block as low as it can get
                    removeFullRowsAndAddPoints(); // removes full rows and adds points, based on the split block this time
                }
            }
        }
        setState(BoardState{StateType::PieceDropped});
        /* by the end, the Game should be able to know:
            1. If we get a special action.
            2. If we lost.
            3. Our updated score.
            4. An updated grid
            5. Updated current piece
            6. Updated new piece
        */
    } else {
        // Invalid command, handle it in Game
    }
    notifyObservers();
}
void Board::setLevel(int lvl) {
    level->setLevel(lvl); // sets the level
    heavy = level->isHeavy(); // is the level heavy?
    splitBlock = level->hasSplitBlock(); // does it have a split block?
    seq->setLevel(lvl); // sets the level of the sequence
    if(lvl == 0) { // if level is 0, we must set a file
        seq->setFile(file0);
    }
}

// getters
int Board::getTurn() const {
    return turn;
}
Piece* Board::getCurPiece() const {
    return curPiece.get();
}
Piece* Board::getNextPiece() const {
    return nextPiece.get();
}
const std::vector<std::vector<Cell>>& Board::getGrid() const {
    return grid;
}
bool Board::getHeavy() const {
    return heavy;
}
bool Board::getBlind() const {
    return blind;
}
int Board::getLevel() const { // returns level number rather than whole level class, this is enough information for Game
    return level->getLevel();
}
bool Board::getSpecial() const {
    return special;
}
bool Board::getDropped() const {
    return dropped;
}
bool Board::getLost() const {
    return lost;
}
int Board::getScore() const {
    return score;
}
int Board::getWidth() const {
    return width;
}
int Board::getHeight() const {
    return height;
}
BoardInfo Board::getInfo() const {
    return BoardInfo{height, width, blind,score,curPiece.get(), nextPiece.get(),grid,id,level->getLevel()};
}
// TODO: need to make attach later


void Board::setSpecial(bool special) {
    this->special = special;
}

void Board::setDropped(bool dropped) {
    this->dropped = dropped;
}
