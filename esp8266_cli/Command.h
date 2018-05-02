#ifndef Command_h
#define Command_h

#include "Cmd.h"

extern bool equalsKeyword(const char* str, const char* keyword);
class Command: public Cmd {
  public:
    Command(const char* name, void(*runFnct)(Cmd*), void(*errorFnct)(uint8_t)) {
      // copy name
      if (name) {
        int strLen = strlen(name);
        Command::name = new char[strLen + 1];
        strcpy(Command::name, name);
        Command::name[strLen] = '\0';
      } else {
        Command::name = new char[1];
        Command::name[0] = '\0';
      }

      Command::runFnct = runFnct;
      Command::errorFnct = errorFnct;
    }

    Command(String name, void(*runFnct)(Cmd*), void(*errorFnct)(uint8_t)) {
      int strLen = name.length() + 1;
      Command::name = new char[strLen];
      name.toCharArray(Command::name, strLen);

      Command::runFnct = runFnct;
      Command::errorFnct = errorFnct;
    }

    ~Command() {
      delete name;
      if (firstArg) delete firstArg;
      if (next) delete next;
    }

    uint8_t equals(const char* name, int argNum, Arg* firstArg){
      bool res;
      
      int strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';
      
      if(!equalsKeyword(tmpName, Command::name))
        return Cmd::WRONG_NAME;
      
      return parse(argNum, firstArg);
    }
    
    uint8_t equals(String name, int argNum, Arg* firstArg){
      if(!equalsKeyword(name.c_str(), Command::name))
        return Cmd::WRONG_NAME;
        
      return parse(argNum, firstArg);
    }
    /*
    bool equalsName(const char* name) {
      return equalsKeyword(name, Command::name);
    }*/
};

#endif

