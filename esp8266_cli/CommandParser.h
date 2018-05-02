#ifndef CommandParser_h
#define CommandParser_h

#include <stddef.h>
#include <stddef.h>
#include <functional>

#include "Arg.h"
#include "Argument.h"
#include "Argument_P.h"

#include "Cmd.h"
#include "Command.h"
#include "Command_P.h"

class CommandParser {
  public:
    void(*onNotFound)(String cmdName) = NULL;
    void(*onParseError)(String invalidArgument) = NULL;

    CommandParser() {

    }

    ~CommandParser() {
      delete firstCmd;
    }

    void parse(String input) {
      int strLen = input.length();

      if (strLen == 0) return;

      const char* str = input.c_str();

      int h = 1;
      int i = 0;

      char prevChar;
      char curChar = str[i];

      while (++i < strLen) {
        prevChar = curChar;
        curChar = str[i];

        if (prevChar == ';' && curChar == ';') {
          parseLine(&str[i - h - 1], h);
          h = 0;
        } else if ((curChar == '\n' || curChar == '\r') && h > 0) {
          parseLine(&str[i - h], h);
          h = 0;
        } else {
          h++;
        }
      }

      if (h > 0) parseLine(&str[i - h], h);
    }

    void parseLine(const char* str, int length) {
      Arg* argList = NULL;
      int argNum = 0;

      bool escaped = false;
      bool inQuotes = false;

      char tmpChar;
      Argument* tmpArg = NULL;

      String tmpStr = String();
      String cmdName = String();

      for (int i = 0; i <= length; i++) {
        if (i < length) tmpChar = str[i];
        else tmpChar = '\0';

        // escape character BACKSLASH
        if (tmpChar == '\\') {
          escaped = !escaped;
          if (escaped) continue;
        }

        // Quotes
        else if (!escaped && tmpChar == '"') {
          inQuotes = !inQuotes;
          continue;
        }

        if (!escaped && !inQuotes && (tmpChar == ' ' || tmpChar == '\r' || tmpChar == '\n' || tmpChar == '\0')) {
          if (tmpStr.length() == 0) continue;

          // save command name
          if (cmdName.length() == 0) {
            cmdName = tmpStr;
          }

          // add argument
          else {

            // add argument to list
            if (tmpStr.charAt(0) == '-') {
              tmpArg = new Argument(tmpStr.substring(1), String(), false);
              tmpArg->next = argList;
              argList = tmpArg;
              argNum++;
            }

            // add value to argument
            else {
              if (tmpArg == NULL) {
                if (onParseError) {
                  onParseError(tmpStr);
                }
              } else {
                tmpArg->setValue(tmpStr);
                tmpArg = NULL; // prevent overwrite of arg value
              }
            }

          }

          tmpStr = String();
        }

        // add chars to temp-string
        else {
          tmpStr += tmpChar;
          escaped = false;
        }

      }

      // go through list to find command
      Cmd* cmd = firstCmd;
      bool found = false;

      while (cmd && !found) {
        uint8_t res = cmd->equals(cmdName, argNum, argList);
        if (res == cmd->OK) {
          cmd->run(cmd);
          found = true;
        } else if (res != cmd->WRONG_NAME) {
          cmd->error(res);
          found = true;
        }
        cmd = cmd->next;
      }

      delete argList;

      if (!found && onNotFound)
        onNotFound(cmdName);
    }

    Cmd* getCommand(String cmdName){
      Cmd* cmd = firstCmd;

      while (cmd) {
        if(cmd->equals(cmdName, 0, NULL) != cmd->WRONG_NAME)
          return cmd;
        cmd = cmd->next;
      }

      return NULL;
    }

    Cmd* getCommand_P(const char* cmdName){
      Cmd* cmd = firstCmd;

      while (cmd) {
        if(cmd->getNamePtr() == cmdName)
          return cmd;
        cmd = cmd->next;
      }

      return NULL;
    }
    
    bool addCommand(Cmd* newCmd) {
      if(getCommand(newCmd->getName()) == NULL){
        newCmd->next = firstCmd;
        firstCmd = newCmd;
        return true;
      }
    }

    bool addCommand(Command* newCmd) {
      return addCommand(static_cast<Cmd*>(newCmd));
    }

    bool addCommand(Command_P* newCmd) {
      if(getCommand_P(newCmd->getNamePtr()) == NULL){
        newCmd->next = firstCmd;
        firstCmd = static_cast<Cmd*>(newCmd);
        return true;
      }
      return false;
    }
  private:
    Cmd* firstCmd = NULL;
};

#endif

