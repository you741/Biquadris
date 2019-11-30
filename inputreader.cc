#include "inputreader.h"
using namespace std;

bool IsIn(const vector<string> &v, const string &s) {
    for (int i=0;i<v.size();++i) 
        if (v[i] == s) return true;
    return false;    
}

Command InputReader::readCommand(bool special) {
    if (in.eof()) {
        return Command {EndOfFile};   
    }
    
    string curline;
    getline(in, curline);
    istringstream iss {curline};
    
    int numToRepeat = 1;
    const vector<string> blockShapes = {"I", "J", "L", "O", "S", "Z", "T"},
        specialCommands = {"heavy", "force", "blind"}, 
        needFileCommands = {"norandom", "sequence"},
        unrepeatableCommands = {"restart"}; 
    
    if (!(iss >> numToRepeat)) {
        iss.clear();
    }
    
    string enteredCommand;
    iss >> enteredCommand;

    if (IsIn(blockShapes, enteredCommand)) {
        return Command {ChangePiece, enteredCommand};
    }
    
    string realCommand;
    int count = 0;
    int index = 0; 
    
    for (int i = 0; i<validCommands.size(); ++i) {
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
            return Command {static_cast<CommandType>(index), true, numToRepeat};
        } else if (IsIn(needFileCommands, realCommand)) {
            string file;
            iss >> file;
            return Command {static_cast<CommandType>(index), file};
        } else if (IsIn(unrepeatableCommands, realCommand)) {
            return Command {static_cast<CommandType>(index)};  
        } else {
            return Command {static_cast<CommandType>(index), numToRepeat};
        }
    }
}   
