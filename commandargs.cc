#include <string>
#include "commandargs.h"
#include <algorithm>    // std::max


using namespace std;

void CommandArgs::setSeed(int s) {
    customSeed = true;
    seed = s;
}

void CommandArgs::setScriptFile(string file, int id) {
    scriptfiles[id] = file;
}

// void CommandArgs::setScriptFile2(string file) {
//     customSF2 = true;
//     scriptfile2 = file;
// }

void CommandArgs::setStartLevel(int level) {
    startLevel = min(level, 4);
}


