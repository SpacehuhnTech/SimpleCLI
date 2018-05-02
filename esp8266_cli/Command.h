#ifndef Command_h
#define Command_h

#include "Cmd.h"

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

    bool equalsName(const char* name) {
      return equalsKeyword(name, Command::name);
    }
};

#endif

