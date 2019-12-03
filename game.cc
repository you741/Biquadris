#include <iostream>
#include <fstream>
#include "textdisplay.h"

#include "game.h"


using namespace std;

Game::Game(CommandArgs ca) {
    // cannot do this in a loop since currently, ca.scriptfile1/2 are not in a vector
    // for (int i = 0; i < numBoards; ++i) {
    //     boards.emplace_back(Board{})
    // }

    // if ca.customSeed is true, then use the seed
    // if ca.scriptfile1 is "", then there is no custom scriptfile
    this->ca = ca;
    boards.emplace_back(Board{ca.customSeed, ca.seed, ca.scriptfile1, ca.startLevel});
    boards.emplace_back(Board{ca.customSeed, ca.seed, ca.scriptfile2, ca.startLevel});

    textOnly = ca.textOnly;
    if (!textOnly) {
        graphics = make_unique<GraphicsDisplay>(boards);
    }
    td = make_unique<TextDisplay>(boards);

    td->updateDisplay(cout);
}

void Game::updateDisplay(int id) {
    cout << "Update display" << endl;
    td->updateDisplay(cout);
    if (!textOnly) {
        graphics->updateDisplay(id);
    }
}

void Game::readInput(istream &in) {
    unique_ptr<InputReader> input = make_unique<InputReader>(in);

    while (!hasWon()) {
        //Get the new command and apply it to curBoard
        Board &curBoard = boards[whoseTurn];
	cout << "Player " << whoseTurn+1 << "'s Turn: ";
        Command c = input->readCommand(false);


        // Either quit if it is coming from user
        //  or the file is done creating inputs
        if (c.commandType == CommandType::EndOfFile) {
            return;
        }

        if (c.commandType == CommandType::Restart) {
            boards[whoseTurn] = Board{ca.customSeed, ca.seed, ca.scriptfile1, ca.startLevel}; // sets a new Board
	    updateDisplay(whoseTurn);
	    return;
        }
        // If command is Sequence, must start reading from the file instead
        if (c.commandType == CommandType::Sequence) {
            ifstream inputFile;
            inputFile.open(c.file);
            if (inputFile.is_open()) {
                readInput(inputFile);
                inputFile.close();
            }
            continue;
        }


        // It is a normal command that is applied like usual
        curBoard.applyCommand(c);
        updateDisplay(whoseTurn);
        // If it is dropped, check if any special actions are triggered.
        //  Switch turns
        if (curBoard.getDropped()) {
            if (curBoard.getSpecial()) {
                Command sc = input->readCommand(true);
                while(sc.commandType == CommandType::INVALID) {
                    sc = input->readCommand(true);
                }
                //Apply the special command to other board
                for (int i = 0; i < numBoards; ++i) {
                    if (i != whoseTurn) {
                        boards[i].applyCommand(sc);
                        if(!textOnly)
                        graphics->updateDisplay(i);
                    }
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
