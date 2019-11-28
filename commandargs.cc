#include <string>
#include "commandargs.h"

using namespace std;

void CommandArgs::setSeed(int s) {
    customSeed = true;
    seed = s;
}

void CommandArgs::setScriptFile1(string file) {
    customSF1 = true;
    scriptfile1 = file;
}

void CommandArgs::setScriptFile2(string file) {
    customSF2 = true;
    scriptfile2 = file;
}

void CommandArgs::setStartLevel(int level) {
    startLevel = level;
}


