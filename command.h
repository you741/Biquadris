#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include "piece.h"

enum CommandType: int { // enum for different command types
    MoveLeft = 0,
    MoveRight,
    MoveDown,
    Clockwise,
    CounterClockwise,
    LevelUp,
    LevelDown,
    NoRandom,
    Random,
    Sequence,
    Restart,
    Heavy,
    Force,
    Blind,
    Drop,
    ChangePiece,
    EndOfFile,
    INVALID
};

struct Command { // command struct will hold any data that is required for the Game and Board to know what kind of Command it is
    CommandType commandType; // type of command
    std::string file = ""; // file name which is required for some commands
    BlockType b = BlockType::I; // BlockType which is required by the ChangePiece command
    bool special = false; // whether the command is special or not
    int rep = 1; // how many times the command is repeated

    // all the constructors
    Command(CommandType c, int rep = 1);
    Command(CommandType c, std::string file, int rep = 1);
    Command(CommandType c, BlockType b, int rep = 1);
    Command(CommandType c, bool special, int rep = 1);
};
#endif
