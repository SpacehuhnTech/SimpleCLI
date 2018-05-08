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

    void Arduino_CLI::parse(const char *input) {
        int strLen = strlen(input);

        if (strLen == 0) return;

        parseLines(input, strLen);
    }

    void Arduino_CLI::parseLines(const char *str, int strLen) {
        int h = 1;
        int i = 0;

        char prevChar;
        char curChar = str[i];

        while (++i < strLen) {
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
        }

        if (h > 0) parseLine(&str[i - h], h);
    }

    void Arduino_CLI::parseLine(const char *str, int strLen) {
        Arg *firstArg = NULL;
        Arg *lastArg  = NULL;

        bool escaped  = false;
        bool inQuotes = false;

        char tmpChar;

        String tmpStr  = String();
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
            else if (!escaped && (tmpChar == '"')) {
                inQuotes = !inQuotes;
                continue;
            }

            if (!escaped && !inQuotes &&
                ((tmpChar == ' ') || (tmpChar == '\r') || (tmpChar == '\n') ||
                 (tmpChar == '\0'))) {
                if (tmpStr.length() == 0) continue;

                // save command name
                if (cmdName.length() == 0) {
                    cmdName = tmpStr;
                }

                // add argument
                else {
                    // add argument to list
                    if (tmpStr.charAt(0) == '-') {
                        Arg *tmpArg = new OptArg(tmpStr.substring(1), String());

                        if (lastArg) lastArg->next = tmpArg;
                        else firstArg = tmpArg;
                        lastArg = tmpArg;
                    }

                    // add value to argument
                    else {
                        bool set = lastArg ? lastArg->isSet() : true;

                        if (set) {
                            Arg *tmpArg = new OptArg(String(), String());

                            if (lastArg) lastArg->next = tmpArg;
                            else firstArg = tmpArg;
                            lastArg = tmpArg;
                            tmpArg->setValue(tmpStr);
                        } else {
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

        /*
           Arg *h = firstArg;

           while (h) {
            Serial.println("\"" + h->getName() + "\":\"" + h->getValue() +
               "\"");
            h = h->next;
           }
         */

        Cmd *cmd   = firstCmd;
        bool found = false;

        while (cmd && !found) {
            if (equals(cmdName.c_str(),
                       cmd->getName().c_str()) >= 0) {
                Arg *hArg = firstArg;

                while (hArg) {
                    cmd->parse(hArg->getName(), hArg->getValue());
                    hArg = hArg->next;
                }

                if (cmd->isSet()) {
                    cmd->run(cmd);
                    found = true;
                }
                cmd->reset();
            }
            cmd = cmd->next;
        }

        delete firstArg;

        if (!found && onNotFound) onNotFound(cmdName);
    }

    Cmd * Arduino_CLI::getCommand(int i) {
        Cmd *h = firstCmd;
        int  j = 0;

        while (h && j < i) {
            h = h->next;
            j++;
        }
        return h;
    }

    Cmd * Arduino_CLI::getCommand(String cmdName) {
        Cmd *h = firstCmd;

        while (h) {
            if (equals(cmdName.c_str(),
                       h->getName().c_str()) >= 0) return h;

            h = h->next;
        }
        return h;
    }

    Cmd * Arduino_CLI::getCommand(const char *cmdName) {
        return getCommand(String(cmdName));
    }

    void Arduino_CLI::addCommand(Cmd *newCmd) {
        if (lastCmd) lastCmd->next = newCmd;

        if (!firstCmd) firstCmd = newCmd;
        lastCmd = newCmd;
        cmdNum++;
    }

#if defined(ESP8266) || defined(ESP32)
    void Arduino_CLI::addCommand(Command *newCmd) {
        addCommand(static_cast<Cmd *>(newCmd));
    }

    void Arduino_CLI::addCommand(Command_P *newCmd) {
        addCommand(static_cast<Cmd *>(newCmd));
    }

    void Arduino_CLI::addCommand(BoundlessCmd *newCmd) {
        addCommand(static_cast<Cmd *>(newCmd));
    }

    void Arduino_CLI::addCommand(BoundlessCmd_P *newCmd) {
        addCommand(static_cast<Cmd *>(newCmd));
    }

    void Arduino_CLI::addCommand(EmptyCmd *newCmd) {
        addCommand(static_cast<Cmd *>(newCmd));
    }

    void Arduino_CLI::addCommand(EmptyCmd_P *newCmd) {
        addCommand(static_cast<Cmd *>(newCmd));
    }

#endif // if defined(ESP8266) || defined(ESP32)
}