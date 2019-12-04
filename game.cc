#include <iostream>
#include <fstream>
#include "textdisplay.h"

#include "game.h"


using namespace std;

Game::Game(CommandArgs ca) {
    // cannot do this in a loop since currently, ca.scriptfile1/2 are not in a vector
    for (int i = 0; i < numBoards; ++i) {
        boards.emplace_back(Board{ca.customSeed, ca.seed, ca.scriptfiles[i], i, ca.startLevel});
    }

    // if ca.customSeed is true, then use the seed
    this->ca = ca;
    textOnly = ca.textOnly;
    if (!textOnly) {
        graphics = make_unique<GraphicsDisplay>(boards);
        for (auto &board: boards) { //attach observers
            board.attach(graphics.get());
            board.initNotify();
        }
    }
    td = make_unique<TextDisplay>(boards);

}

void Game::updateDisplay(int id) {
    td->updateDisplay(cout);
}

// to read special commands when 2+ lines are cleared
bool Game::readSpecialCommand(istream &in) {
	unique_ptr<InputReader> input = make_unique<InputReader>(in);
	cout << "Player " << whoseTurn+1 << ", enter a special command (blind/heavy/force [block type]): " << endl;
	Command sc = input->readCommand(true);
    while(sc.commandType == CommandType::INVALID) {
        cout << "Invalid special command, try again (blind/heavy/force [block type]): " << endl;
        sc = input->readCommand(true);
    }
	if(sc.commandType == CommandType::EndOfFile) { // lets Game know it is end of file, so we can send the message to the caller
	    return false;
	}
    //Apply the special command to other board
    for (int i = 0; i < numBoards; ++i) {
        if (i != whoseTurn) {
            boards[i].applyCommand(sc);
        }
    }
	return true;
}

// core loop of the game, will continuously run to play the game
bool Game::readInput(istream &in) {
    unique_ptr<InputReader> input = make_unique<InputReader>(in);
    bool sequenceAsksForSpecial = false;
    while (!hasWon()) {
        //Get the new command and apply it to curBoard
        Board &curBoard = boards[whoseTurn];

        // when sequence file triggers special but does not give a special but an EOF instead
        if(sequenceAsksForSpecial) {
            if(!readSpecialCommand(in)) {
                return true; // if we get false, that means readSpecialCommand got an EOF and we just return true to let the caller know
            }
            // if the special succeeded
            updateDisplay(whoseTurn);
            curBoard.setSpecial(false);
            sequenceAsksForSpecial = false;
            curBoard.setDropped(false);
            nextTurn();
            continue;
        }

        cout << "Player " << whoseTurn+1 << "'s Turn: " << endl;

        Command c = input->readCommand(false);

        // Either quit if it is coming from user
        //  or the file is done creating inputs
        if (c.commandType == CommandType::EndOfFile) {
            cout << "End of File" << endl;
            return false;
        }

        if (c.commandType == CommandType::Restart) {
            boards[whoseTurn] = Board{ca.customSeed, ca.seed, ca.scriptfiles[whoseTurn], whoseTurn, ca.startLevel}; // sets a new Board
            updateDisplay(whoseTurn);
            if (!textOnly) {
                boards[whoseTurn].attach(graphics.get()); // reattach the observer
                boards[whoseTurn].initNotify();
            }
            continue;
        }
        // If command is Sequence, must start reading from the file instead
        if (c.commandType == CommandType::Sequence) {
            ifstream inputFile;
            inputFile.open(c.file);
            if (inputFile.is_open()) {
                sequenceAsksForSpecial = readInput(inputFile);
                inputFile.close();
            }
            continue;
        }

        if(c.commandType == CommandType::INVALID) {
            cout << "Invalid command." << endl;
            continue;
        }

        // It is a normal command that is applied like usual
        curBoard.applyCommand(c);
        updateDisplay(whoseTurn);
        // If it is dropped, check if any special actions are triggered.
        //  Switch turns
        if (curBoard.getDropped()) {
            if (curBoard.getSpecial()) {
                if(!readSpecialCommand(in)) {
                    return true; // if we get false, that means readSpecialCommand got an EOF and we just return true to let the caller know
                }
                updateDisplay(whoseTurn);
                curBoard.setSpecial(false);
            }
            curBoard.setDropped(false);
            nextTurn();
        }
    }
    for (int i=0; i<numBoards;++i) {
        winnerScore = max(winnerScore, boards[i].getScore());
    }
    return false;
}

void Game::nextTurn() {
    ++whoseTurn;
    whoseTurn %= numBoards;
}

int Game::getWinnerScore() {
    return winnerScore;
}

bool Game::hasWon() {
    int alive = 0;
    for (int i = 0; i < numBoards; ++i) {
        if (!boards[i].getLost()) {
            ++alive;
        }
    }
    return (alive == 1);
}


int Game::returnWinner() {
    for (int i = 0; i < numBoards; ++i) {
        if (!boards[i].getLost()) {
            return i;
        }
    }
    return -1;
}

Board& Game::getBoard(int target) {
    return boards[target];
}
