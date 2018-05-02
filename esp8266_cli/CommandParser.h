#ifndef CommandParser_h
#define CommandParser_h

#include "Arduino.h"
extern "C" {
#include "user_interface.h"
}

#include "Arg.h"
#include "Argument.h"
#include "Argument_P.h"

#include "Cmd.h"
#include "Command.h"
#include "Command_P.h"

const char EMPTY_PROGMEM_STRING[] PROGMEM = " ";
bool equalsKeyword(const char* str, const char* keyword) {
  if (!str) return false;
  if (!keyword) return false;

  int lenStr = strlen(str);
  int lenKeyword = strlen(keyword);

  // string can't be longer than keyword (but can be smaller because of '/' and ',')
  if (lenStr > lenKeyword)
    return false;

  if (lenStr == lenKeyword)
    return strcmp(str, keyword) == 0;

  int a = 0;
  int b = 0;
  bool result = true;

  while (a < lenStr && b < lenKeyword) {
    if (keyword[b] == '/') {
      b++;
    } else if (keyword[b] == ',') {
      b++;
      a = 0;
    }

    if (tolower(str[a]) != tolower(keyword[b])) {
      result = false;
    }

    // fast forward to next comma
    if ((a == lenStr && !result) || !result) {
      while (b < lenKeyword && keyword[b] != ',') b++;
      result = true;
    } else {
      a++;
      b++;
    }
  }
  // comparison correct AND string checked until the end AND keyword checked until the end
  result = result && a == lenStr && (keyword[b] == ',' || keyword[b] == '/' || keyword[b] == '\0');
  return result;
}

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

      parseLines(str, strLen);
    }

    void parse(const char* input) {
      int strLen = strlen_P(input);

      if (strLen == 0) return;

      char tmpInput[strLen + 1];
      strcpy_P(tmpInput, input);
      tmpInput[strLen] = '\0';

      parseLines(tmpInput, strLen);
    }

    void parseLines(const char* str, int strLen) {
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

    void parseLine(const char* str, int strLen) {
      Arg* argList = NULL;
      int argNum = 0;

      bool escaped = false;
      bool inQuotes = false;

      char tmpChar;
      Argument* tmpArg = NULL;

      String tmpStr = String();
      String cmdName = String();

      for (int i = 0; i <= strLen; i++) {
        if (i < strLen) tmpChar = str[i];
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
        if (res != cmd->WRONG_NAME) {
          found = true;
          
          if(res == cmd->OK)
            cmd->run(cmd);
          else
            cmd->error(res);
        }
        cmd = cmd->next;
      }

      delete argList;

      if (!found && onNotFound)
        onNotFound(cmdName);
    }

    Cmd* getCommand(String cmdName) {
      Cmd* cmd = firstCmd;

      while (cmd) {
        if (cmd->equals(cmdName, 0, NULL) != cmd->WRONG_NAME)
          return cmd;
        cmd = cmd->next;
      }

      return NULL;
    }

    Cmd* getCommand_P(const char* cmdName) {
      Cmd* cmd = firstCmd;

      while (cmd) {
        if (cmd->getNamePtr() == cmdName)
          return cmd;
        cmd = cmd->next;
      }

      return NULL;
    }

    bool addCommand(Cmd* newCmd) {
      if (getCommand(newCmd->getName()) == NULL) {
        newCmd->next = firstCmd;
        firstCmd = newCmd;
        return true;
      }
    }

    bool addCommand(Command* newCmd) {
      return addCommand(static_cast<Cmd*>(newCmd));
    }

    bool addCommand(Command_P* newCmd) {
      if (getCommand_P(newCmd->getNamePtr()) == NULL) {
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

