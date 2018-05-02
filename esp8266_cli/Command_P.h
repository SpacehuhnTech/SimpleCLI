#ifndef Command_P_h
#define Command_P_h

#include "Cmd.h"

extern const char EMPTY_PROGMEM_STRING[] PROGMEM;

class Command_P: public Cmd {
  public:
    Command_P(const char* name, void(*runFnct)(Cmd*), void(*errorFnct)(uint8_t) ) {
      if(!name) name = EMPTY_PROGMEM_STRING;
      
      Command_P::runFnct = runFnct;
      Command_P::errorFnct = errorFnct;
      Command_P::name = const_cast<char*>(name);
    }

    ~Command_P() {
      if (firstArg) delete firstArg;
      if (next) delete next;
    }

    uint8_t equals(const char* name, int argNum, Arg* firstArg){
      bool res;
      int strLen;
      
      strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      strLen = strlen_P(Command_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, Command_P::name);
      tmpKeyword[strLen] = '\0';

      if(!equalsKeyword(tmpName, tmpKeyword))
        return Cmd::WRONG_NAME;
      
      return parse(argNum, firstArg);     
    }
    
    uint8_t equals(String name, int argNum, Arg* firstArg){
      bool res;
      
      int strLen = strlen_P(Command_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, Command_P::name);
      tmpKeyword[strLen] = '\0';

      if(!equalsKeyword(name.c_str(), tmpKeyword))
        return Cmd::WRONG_NAME;

      return parse(argNum, firstArg);
    }
};

#endif

