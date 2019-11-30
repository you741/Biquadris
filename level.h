#ifndef LEVEL_H
#define LEVEL_H
#include <vector>

class Level { // this class makes it easier to find what a level contains
    int level = 0;
    std::vector<bool> heavys;
    std::vector<bool> randoms;
    std::vector<bool> splitBlock; // split blocks are the blocks that fall down in the middle every 5 turns without clearing
public:
    Level(int level = 0);
    void setLevel(int level);
    int getLevel() const;
    bool isHeavy() const;
    bool isRandom() const;
    bool hasSplitBlock() const;
};
#endif // LEVEL_H
