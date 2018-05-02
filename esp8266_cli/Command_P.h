#ifndef Command_P_h
#define Command_P_h

#include "Cmd.h"

class Command_P: public Cmd {
  public:
    Command_P(const char* name, void(*runFnct)(Cmd*), void(*errorFnct)(uint8_t) ) {
      Command_P::runFnct = runFnct;
      Command_P::errorFnct = errorFnct;
      Command_P::name = const_cast<char*>(name);
    }

    ~Command_P() {
      if (firstArg) delete firstArg;
      if (next) delete next;
    }

    bool equalsName(const char* name) {
      int tmpNameLen = strlen_P(Command_P::name);
      char* tmpName = new char[tmpNameLen + 1];
      strcpy_P(tmpName, Command_P::name);
      tmpName[tmpNameLen] = '\0';

      bool res = equalsKeyword(name, tmpName);
      delete tmpName;
      return res;
    }
};

#endif

