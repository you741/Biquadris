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
    Game g = Game{ca};
    g.readInput(cin);

}
