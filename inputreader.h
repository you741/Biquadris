#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "command.h"

class InputReader {
    std::istream& in = std::cin;
    std::vector<std::string> validCommands = {
        "left", "right", "down",
        "clockwise", "counterclockwise",
        "levelup", "leveldown",
        "norandom","random", "sequence",
        "restart", "heavy", "force", "blind","drop",
        "I", "J", "L",
        "O", "S", "Z", "T"
    };

    public:
    InputReader() = default;
    InputReader(std::istream &in);
    ~InputReader() = default;
    InputReader(const InputReader& other) = delete;
    InputReader operator=(const InputReader& other) = delete;
    Command readCommand(bool special = false);
};

#endif
