#ifndef __ROTATE_H__
#define __ROTATE_H__
#include "command.h"
class RotateCommand: public Command { // handles rotating the block using the board as the model
    bool clockwise = true;
   public:
    RotateCommand(bool clockwise = true);
    void apply(Board *b);
};
#endif // __ROTATE_H__
