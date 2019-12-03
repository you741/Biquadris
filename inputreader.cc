#include "inputreader.h"
#include "block.h"

using namespace std;

bool IsIn(const vector<string> &v, const string &s) {
    for (unsigned i=0;i<v.size();++i)
        if (v[i] == s) return true;
    return false;
}

InputReader::InputReader(istream& in): in {in} {};

Command InputReader::readCommand(bool special) {
    if (in.eof()) {
        return Command {EndOfFile};
    }
    string curline;
    if(!getline(in, curline)) {
	return Command {EndOfFile};
    }
    istringstream iss {curline};
    int numToRepeat = 1;
    const vector<string> blockShapes = {"I", "J", "L", "O", "S", "Z", "T"},
        specialCommands = {"heavy", "force", "blind"},
        needFileCommands = {"norandom", "sequence"},
        unrepeatableCommands = {"restart"};

    if (!(iss >> numToRepeat)) {
        numToRepeat = 1;
	iss.clear();
    }
    string enteredCommand;
    iss >> enteredCommand;
    if (special) { // forces command to be special, otherwise invalid
        for (unsigned i=0;i<validCommands.size();++i) {
            if (validCommands[i].find(enteredCommand) == 0 && IsIn(specialCommands, validCommands[i])) {
                if (validCommands[i] == "force") {
                    string block;
                    if (!(iss >> block)) {
                        return Command {INVALID};
                    }
                    return Command {static_cast<CommandType>(i), static_cast<BlockType>(block[0])};
                }
                return Command {static_cast<CommandType>(i), numToRepeat};
            }
        }
        return Command {INVALID};
    }

    if (IsIn(blockShapes, enteredCommand)) { // handles the single character commands, they are special
        return Command {ChangePiece, static_cast<BlockType>(enteredCommand[0])};
    }

    string realCommand;
    int count = 0;
    int index = 0;

    for (unsigned i = 0; i<validCommands.size(); ++i) {
        if (validCommands[i].find(enteredCommand) == 0) {
            count++;
            realCommand = validCommands[i];
            index = i;
        }
    }

    if (count != 1) {
        return Command {INVALID};
    } else {
        if (IsIn(specialCommands, realCommand)) {
            return Command {INVALID};
        } else if (IsIn(needFileCommands, realCommand)) {
            string file;
            if (!(iss >> file)) {
                return Command {INVALID};
            }
            return Command {static_cast<CommandType>(index), file};
        } else if (IsIn(unrepeatableCommands, realCommand)) {
            return Command {static_cast<CommandType>(index)};
        } else {
            return Command {static_cast<CommandType>(index), numToRepeat};
        }
    }
}
