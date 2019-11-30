#include "level.h"

using namespace std;


Level::Level(int level): level{level},
    heavys{false,false,false,true,true},
    randoms{false,true,true,true,true},
    splitBlock{false,false,false,false,true} { // stores the default settings for each level
    }

void Level::setLevel(int level) {
    this->level = level;
}
int Level::getLevel() const {
    return level;
}
bool Level::isHeavy() const {
    return heavys[level];
}
bool Level::isRandom() const {
    return randoms[level];
}

bool Level::hasSplitBlock() const {
    return splitBlock[level];
}
