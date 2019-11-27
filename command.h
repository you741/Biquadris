#ifndef __COMMAND_H__
#define __COMMAND_H__
#include "board.h"
#include "block.h"
#include "force.h"
#include "heavy.h"
#include "blind.h"
#include "changepiece.h"
#include "random.h"
#include "drop.h"
#include "rotate.h"
#include "move.h"
#include "level.h"

enum CommandType { // enum for different command types
  Force,
  Heavy,
  Blind,
  ChangePiece,
  NoRandom,
  Random,
  Drop,
  Rotate,
  CounterClockwise,
  Move,
  Level
};

class Command { // command class will generate specialized commands using its getCommand static method
   protected:
    bool special = false; // special commands are applied to the opponent, so we need a way to distinguish them
   public:
    static Command *getCommand(CommandType c);
    static Command *getCommand(CommandType c, BlockType b);
    static Command *getCommand(CommandType c, int change);
    static Command *getCommand(CommandType c, int r, int d);
    bool isSpecial();
    virtual void apply(Board *b) = 0;
};
#endif
