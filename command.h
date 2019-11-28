#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include "piece.h"

enum CommandType { // enum for different command types
  Force,
  Heavy,
  Blind,
  ChangePiece,
  NoRandom,
  Random,
  Drop,
  Clockwise,
  CounterClockwise,
  MoveLeft,
  MoveRight,
  MoveDown,
  LevelUp,
  LevelDown,
  Sequence,
  EOF
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
