#ifndef COMMANDARGS_H
#define COMMANDARGS_H
#include <string>

//Should just make all this public/struct so there will be no need
// for getter methods

struct CommandArgs{
    bool textOnly = false;
    bool customSeed = false;
    int seed = 0;
    bool customSF1 = false;
    bool customSF2 = false;
    std::string scriptfile1 = "";
    std::string scriptfile2 = "";
    int startLevel = 0;
  
    void setSeed(int s);
    void setScriptFile1(std::string file);
    void setScriptFile2(std::string file);
    void setStartLevel(int level);

};

#endif
