#include <string>
#include <iostream>
#include "commandargs.h"
#include "game.h"

using namespace std;

int main(int argc, char *argv[]) {
    CommandArgs ca;

    int i = 1;
    string input;
    while (i < argc) {
        input = string(argv[i]);

        if (input == "-text") {
            ca.textOnly = true;
        } else if (input == "-seed") {
            ca.setSeed(stoi(string(argv[++i])));
        } else if (input == "-scriptfile1") {
            ca.setScriptFile1(string(argv[++i]));
        } else if (input == "-scriptfile2") {
            ca.setScriptFile2(string(argv[++i]));
        } else if (input == "-startlevel") {
            ca.setStartLevel(stoi(string(argv[++i])));
        }

        ++i;
    }
    // Create and run game
    int hiScore = 0;
    while (true) {
        Game g = Game{ca};
        g.readInput(cin);
        hiScore = max(hiScore,g.getWinnerScore());
        if (g.getWinnerScore() == -1) {
            continue;
        } else {
            cout << "The winner of this game, Player" << g.returnWinner() << ", scored " << g.getWinnerScore() << "points," << endl;
            cout << "want to continue playing?[y/n]" << endl;
            std::string decision;
            bool wantToContinue = false;
            while (cin >> decision) {
                if (decision == "y") {
                     wantToContinue = true;
                     break;
                } else if (decision == "n") {
                    return 0;
                } else {
                    cout << "Please enter either 'y' or 'n'." << endl;
                }
            }
            if (wantToContinue) {
                continue;
            }
        }
    }
}
