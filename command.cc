#include "command.h"
#include "block.h"
Command* Command::getCommand(CommandType c) {
    if(c == CommandType::Force) {
        return new ForceCommand();
    }
    else if(c == CommandType::Heavy) {
        return new HeaveyCommand();
    }
    else if(c == CommandType::Blind) {
        return new BlindCommand();
    }
    else if(c == CommandType::Random) {
        return new RandomCommand();
    }
    else if (c == CommandType::NoRandom) {
        return new RandomCommand(true);
    }
    else if(c == CommandType::Drop) {
        return new DropCommand();
    }
    else if(c == CommandType::Rotate) {
        return new RotateCommand();
    }
    else if(c == CommandType::CounterClockwise) {
        return new RotateCommand(false);
    } else {
        return nullptr;
    }
}
Command* Command::getCommand(CommandType c, BlockType b) {
    if(c == CommandType::ChangePiece) {
        return new ChangePieceCommand(b);
    } else {
        return getCommand(c);
    }
}

Command* Command::getCommand(CommandType c, int change) {
    if(c == CommandType::Level) {
        return new LevelCommand(change);
    } else {
        return getCommand(c);
    }
}

Command* Command::getCommand(CommandType c, int r, int d) {
    if(c == CommandType::Move) {
        return new MoveCommand(r,d);
    } else {
        return getCommand(c,r);
    }
}

bool Command::isSpecial() {
    return special;
}
