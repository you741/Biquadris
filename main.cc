#include <string>
#include <iostream>
#include <fstream>
#include "commandargs.h"
#include "game.h"

using namespace std;

int main(int argc, char *argv[]) {
    CommandArgs ca;
    int i = 1;
    string input;
    while (i < argc) {
        // read command line arguments
        input = string(argv[i]);

        if (input == "-text") {
            ca.textOnly = true;
        } else if (input == "-seed") {
            ca.setSeed(stoi(string(argv[++i])));
        } else if (input == "-scriptfile1") {
            ca.setScriptFile(string(argv[++i]), 0);
        } else if (input == "-scriptfile2") {
            ca.setScriptFile(string(argv[++i]), 1);
        } else if (input == "-startlevel") {
            ca.setStartLevel(stoi(string(argv[++i])));
        }

        ++i;
    }
    // Create and run game
    int hiScore = 0;
    ifstream ifs {"record.txt"};
    if (!ifs.fail()) {
        ifs >> hiScore;
    }
    ifs.close();
    while (true) {
        Game g = Game{ca};
        g.readInput(cin);
        hiScore = max(hiScore,g.getWinnerScore());
        if (g.getWinnerScore() == -1) {
            continue;
        } else {
            cout << "The winner of this game, Player " << g.returnWinner() + 1 << ", scored " << g.getWinnerScore() << " points," << endl;
            cout << "The highest score ever is: " << hiScore << "." << endl;
            cout << "want to continue playing?[y/n]" << endl;
            std::string decision;
            bool wantToContinue = false;
            while (getline(cin,decision)) {
                if (decision == "y") {
                     wantToContinue = true;
                     break;
                } else if (decision == "n") {
		     break;
                } else {
                    cout << "Please enter either 'y' or 'n'." << endl;
                }
            }
            if (!wantToContinue) {
                break;
            }
        }
    }
    ofstream ofs {"record.txt"};
    ofs << hiScore << endl;
    ofs.close();
    return 0;
}
