#include <iostream>
#include <fstream>
#include "game.h"


using namespace std;

Game::Game(CommandArgs ca) {
    // cannot do this in a loop since currently, ca.scriptfile1/2 are not in a vector
    // for (int i = 0; i < numBoards; ++i) {
    //     boards.emplace_back(Board{})
    // }

    // if ca.customSeed is true, then use the seed
    // if ca.scriptfile1 is "", then there is no custom scriptfile
    boards.emplace_back(Board{ca.customSeed, ca.seed, ca.scriptfile1, ca.startLevel});
    boards.emplace_back(Board{ca.customSeed, ca.seed, ca.scriptfile2, ca.startLevel});
    graphics = make_unique<GraphicsDisplay>();
    td = make_unique<TextDisplay>(boards);
}

void Game::readInput(istream &in) {
    unique_ptr<InputReader> input = make_unique<InputReader>(in);

    while (!hasWon()) {
        //Get the new command and apply it to curBoard
        Board &curBoard = boards[whoseTurn];
        Command &c = input.readCommand(false);


        // Either quit if it is coming from user
        //  or the file is done creating inputs
        if (c.commandType == CommandType::EOF) {
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
        curBoard.apply(c);

        // If it is dropped, check if any special actions are triggered.
        //  Switch turns 
        if (c.commandType == CommandType::Drop) {
            if (curBoard.getSpecial()) {
                Command &sc = input.readCommand(true);
                //Apply the special command to other board
                for (int i = 0; i < numBoards; ++i) {
                    if (i != whoseTurn) {
                        sc.apply(boards[i]);
                    }
                }
            }
            nextTurn();
        }
        
    }
}

void Game::nextTurn() {
    ++whoseTurn;
    whoseTurn %= numBoards;
}


bool Game::hasWon() {
    int alive = 0;
    for (int i = 0; i < numBoards; ++i) {
        if (!boards[i].lost) {
            ++alive;
        }
    }
    return (alive == 1);
}


int Game::returnWinner() {
    for (int i = 0; i < numBoards; ++i) {
        if (!boards[i].lost) {
            return i;
        }
    }
}

Board Game::getBoard(int target) {
    return boards[target];
}


