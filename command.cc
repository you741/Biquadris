#include "command.h"

using namespace std;

Command::Command(CommandType c, int rep): commandType{c}, rep{rep} { // sets default special commands to have special = true
    if(c == CommandType::Force) {
        this->special = true;
    } else if (c == CommandType::Heavy) {
        this->special = true;
    } else if (c == CommandType::Blind) {
        this->special = true;
    }
}

Command::Command(CommandType c, std::string file, int rep): commandType{c}, file{file}, rep{rep} {}

Command::Command(CommandType c, BlockType b, int rep): commandType{c}, b{b}, rep{rep} {}

Command::Command(CommandType c, bool special, int rep): commandType{c}, special{special}, rep{rep} {}
