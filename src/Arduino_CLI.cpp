#include "Arduino_CLI.h"

namespace arduino_cli {
    Arduino_CLI::Arduino_CLI() {}

    Arduino_CLI::~Arduino_CLI() {
        delete firstCmd;
    }

    void Arduino_CLI::parse(String input) {
        int strLen = input.length();

        if (strLen == 0) return;

        parseLines(input.c_str(), strLen);
    }

    void Arduino_CLI::parse(const char* input) {
        int strLen = strlen(input);

        if (strLen == 0) return;

        parseLines(input, strLen);
    }

    void Arduino_CLI::parseLines(const char* str, int strLen) {
        if (strLen == 0) return;

        int h = 0;
        int i = 0;

        char prevChar;
        char curChar;

        while (i < strLen) {
            prevChar = curChar;
            curChar  = str[i];

            if ((prevChar == ';') && (curChar == ';')) {
                parseLine(&str[i - h - 1], h);
                h = 0;
            } else if (((curChar == '\n') || (curChar == '\r')) && (h > 0)) {
                parseLine(&str[i - h], h);
                h = 0;
            } else {
                h++;
            }

            i++;
        }

        if (h > 0) parseLine(&str[i - h], h);
    }

    void Arduino_CLI::parseLine(const char* str, int strLen) {
        if (strLen == 0) return;

        Arg* firstArg = NULL;
        Arg* lastArg  = NULL;

        bool escaped  = false;
        bool inQuotes = false;

        char tmpChar = str[0];

        String tmpStr  = String();
        String cmdName = String();

        int i = 0;

        // get cmdName
        while (tmpChar != ' ' && i < strLen) {
            tmpChar = str[i];

            if (tmpChar != ' ') cmdName += String(tmpChar);
            i++;
        }

        // search for command with given name
        Cmd* cmd = getNextCmd(firstCmd, cmdName);

        // when no command found, quick exit
        if (!cmd) {
            if (onNotFound) onNotFound(cmdName);
            return;
        }

        // check for SingleArgCmd's
        if (cmd->argNum() == -1) {
            cmd->parse(String(), String(&str[i]));
            cmd->run(cmd);
            cmd->reset();
            return;
        }

        // get arguments
        while (i <= strLen) {
            if (i < strLen) tmpChar = str[i];
            else tmpChar = '\0';

            // escape character BACKSLASH
            if (tmpChar == '\\') {
                escaped = !escaped;

                if (escaped) continue;
            }

            // Quotes
            else if (!escaped && (tmpChar == '"')) {
                inQuotes = !inQuotes;
                continue;
            }

            if (!escaped && !inQuotes &&
                ((tmpChar == ' ') || (tmpChar == '\r') || (tmpChar == '\n') || (tmpChar == '\0'))) {
                if (tmpStr.length() > 0) {
                    // add argument to list
                    if ((tmpStr.charAt(0) == '-') && (tmpStr.length() > 1)) {
                        Arg* tmpArg = new OptArg(tmpStr.substring(1), String());

                        if (lastArg) lastArg->next = tmpArg;
                        else firstArg = tmpArg;
                        lastArg = tmpArg;
                    }

                    // add value to argument
                    else {
                        bool set = lastArg ? lastArg->isSet() : true;

                        if (set) {
                            Arg* tmpArg = new OptArg(String(), String());

                            if (lastArg) lastArg->next = tmpArg;
                            else firstArg = tmpArg;
                            lastArg = tmpArg;
                            tmpArg->setValue(tmpStr);
                        } else {
                            lastArg->setValue(tmpStr);
                        }
                    }

                    tmpStr = String();
                }
            }

            // add chars to temp-string
            else {
                tmpStr += String(tmpChar);
                escaped = false;
            }

            i++;
        }

        /*
           Arg *h = firstArg;

           while (h) {
            Serial.println("\"" + h->getName() + "\":\"" + h->getValue() +
               "\"");
            h = h->next;
           }
         */

        bool found = false;

        do {
            Arg* hArg = firstArg;

            while (hArg) {
                cmd->parse(hArg->getName(), hArg->getValue());
                hArg = hArg->next;
            }

            if (cmd->isSet()) {
                cmd->run(cmd);
                found = true;
            }
            cmd->reset();

            cmd = getNextCmd(cmd->next, cmdName);
        } while (!found && cmd);

        delete firstArg;

        if (!found && onNotFound) onNotFound(cmdName);
    }

    Cmd* Arduino_CLI::getCmd(int i) {
        Cmd* h = firstCmd;
        int  j = 0;

        while (h && j < i) {
            h = h->next;
            j++;
        }
        return h;
    }

    Cmd* Arduino_CLI::getCmd(String cmdName) {
        return getNextCmd(firstCmd, cmdName);
    }

    Cmd* Arduino_CLI::getNextCmd(Cmd* begin, String cmdName) {
        Cmd* h = begin;

        while (h) {
            if (equals(cmdName.c_str(), h->getName().c_str()) >= 0) return h;

            h = h->next;
        }
        return h;
    }

    Cmd* Arduino_CLI::getCmd(const char* cmdName) {
        return getNextCmd(firstCmd, cmdName);
    }

    Cmd* Arduino_CLI::getNextCmd(Cmd* begin, const char* cmdName) {
        Cmd* h = begin;

        while (h) {
            if (equals(cmdName, h->getName().c_str()) >= 0) return h;

            h = h->next;
        }
        return h;
    }

    void Arduino_CLI::addCmd(Cmd* newCmd) {
        if (lastCmd) lastCmd->next = newCmd;

        if (!firstCmd) firstCmd = newCmd;
        lastCmd = newCmd;
        cmdNum++;
    }

    void Arduino_CLI::addCmd(Command* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void Arduino_CLI::addCmd(BoundlessCmd* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void Arduino_CLI::addCmd(EmptyCmd* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void Arduino_CLI::addCmd(SingleArgCmd* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void Arduino_CLI::addCmd(Command_P* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void Arduino_CLI::addCmd(BoundlessCmd_P* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void Arduino_CLI::addCmd(EmptyCmd_P* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void Arduino_CLI::addCmd(SingleArgCmd_P* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void Arduino_CLI::setCaseSensetive() {
        arduino_cli::caseSensetive = true;
    }
}