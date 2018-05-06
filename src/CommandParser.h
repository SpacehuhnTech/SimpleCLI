#ifndef CommandParser_h
#define CommandParser_h

#include "cli_helper.h"
#include "Arg.h"
#include "Cmd.h"
#include "BoundlessCmd.h"
#include "BoundlessCmd_P.h"
#include "Command.h"
#include "Command_P.h"
#include "EmptyCmd.h"
#include "EmptyCmd_P.h"

class CommandParser {
  public:
    void(*onNotFound)(String cmdName) = NULL;
    
    CommandParser() {

    }

    ~CommandParser() {
      delete firstCmd;
    }

    void parse(String input) {
      int strLen = input.length();
      if (strLen == 0) return;
      parseLines(input.c_str(), strLen);
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
      Arg* firstArg = NULL;
      Arg* lastArg = NULL;

      bool escaped = false;
      bool inQuotes = false;

      char tmpChar;

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
              Arg* tmpArg = new OptArg(tmpStr.substring(1), String());
              if(lastArg) lastArg->next = tmpArg;
              else firstArg = tmpArg;
              lastArg = tmpArg;
            }

            // add value to argument
            else {
              bool set = lastArg ? lastArg->isSet() : true;
              
              if(set){
                Arg* tmpArg = new OptArg(String(), String());
                if(lastArg) lastArg->next = tmpArg;
                else firstArg = tmpArg;
                lastArg = tmpArg;
                tmpArg->setValue(tmpStr);
              }else{
                lastArg->setValue(tmpStr);
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
      
      /*Arg* h = firstArg;
      while(h){
        Serial.println("\""+h->getName()+"\":\""+h->getValue()+"\"");
        h = h->next;
      }*/

      Cmd* cmd = firstCmd;
      bool found = false;
      
      while (cmd && !found) {
        if(cli_helper::equals(cmdName.c_str(), cmd->getName().c_str())){
          Arg* hArg = firstArg;
          while(hArg){
            cmd->parse(hArg->getName(), hArg->getValue());
            hArg = hArg->next;
          }
          if(cmd->isSet()){
            cmd->run(cmd);
            found = true;
          }
          cmd->reset();
        }
        cmd = cmd->next;
      }

      delete firstArg;

      if (!found && onNotFound)
        onNotFound(cmdName);
    }


    Cmd* getCommand(int i) {
      Cmd* h = firstCmd;
      int j = 0;
      while(h && j<i){
        h = h->next;
        j++;
      }
      return h;
    }

    Cmd* getCommand(String cmdName) {
      Cmd* h = firstCmd;
      while(h){
        if(cli_helper::equals(cmdName.c_str(), h->getName().c_str()))
          return h;
        h = h->next;
      }
      return h;
    }

    Cmd* getCommand(const char* cmdName) {
      return getCommand(String(cmdName));
    }
    
    void addCommand(Cmd* newCmd) {
      if(lastCmd) lastCmd->next = newCmd;
      if(!firstCmd) firstCmd = newCmd;
      lastCmd = newCmd;
      cmdNum++;
    }
    
    void addCommand(Command* newCmd){ addCommand(static_cast<Cmd*>(newCmd)); }
    void addCommand(Command_P* newCmd){ addCommand(static_cast<Cmd*>(newCmd)); }
    void addCommand(BoundlessCmd* newCmd){ addCommand(static_cast<Cmd*>(newCmd)); }
    void addCommand(BoundlessCmd_P* newCmd){ addCommand(static_cast<Cmd*>(newCmd)); }
    void addCommand(EmptyCmd* newCmd){ addCommand(static_cast<Cmd*>(newCmd)); }
    void addCommand(EmptyCmd_P* newCmd){ addCommand(static_cast<Cmd*>(newCmd)); }
  private:
    int cmdNum = 0;
    Cmd* firstCmd = NULL;
    Cmd* lastCmd = NULL;
};

#endif

