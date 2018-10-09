#include "SimpleCLI.h"

namespace simplecli {
    SimpleCLI::SimpleCLI() {}

    SimpleCLI::~SimpleCLI() {
        delete firstCmd;
    }

    void SimpleCLI::parse(String input) {
        if (input.length() > 0) parseLines(input);
    }

    void SimpleCLI::parseLines(String& input) {
        int strLen = input.length();

        if (strLen == 0) return;

        char c;

        String line;

        for (int i = 0; i < strLen; i++) {
            c = input.charAt(i);

            if ((c == ';') && (input.charAt(i + 1) == ';')) {
                parseLine(line);
                i++;
                line = String();
            } else if ((c == '\n') || (c == '\r')) {
                parseLine(line);
                line = String();
            } else {
                line += c;
            }
        }

        parseLine(line);
    }

    void SimpleCLI::parseLine(String& input) {
        int strLen = input.length();

        if (strLen == 0) return;

        String cmdName = readCmdName(input);

        // search for command with given name
        Cmd* cmd = getNextCmd(firstCmd, cmdName);

        // when no command found, quick exit
        if (!cmd) {
            if (onNotFound) onNotFound(cmdName);
            return;
        }

        // check for SingleArgCmd's
        if (cmd->argNum() == -1) {
            cmd->parse(String(), input);
            cmd->run(cmd);
            cmd->reset();
            return;
        }

        // get arguments
        String argName;
        Arg  * firstArg = NULL;
        Arg  * lastArg  = NULL;

        while (input.length() > 0) {
            // read argument from string
            argName = getNextArg(input);

            // when empty, continue
            if (argName.length() == 0) continue;

            // add argument to list
            if ((argName.charAt(0) == '-') && (argName.length() > 1)) {
                Arg* tmpArg = new OptArg(argName.substring(1).c_str());

                if (lastArg) lastArg->next = tmpArg;
                else firstArg = tmpArg;
                lastArg = tmpArg;
            }

            // add value to argument
            else {
                bool set = lastArg ? lastArg->isSet() : true;

                if (set) {
                    Arg* tmpArg = new OptArg(NULL);

                    if (lastArg) lastArg->next = tmpArg;
                    else firstArg = tmpArg;
                    lastArg = tmpArg;
                    tmpArg->setValue(argName);
                } else {
                    lastArg->setValue(argName);
                }
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

    Cmd* SimpleCLI::getCmd(int i) {
        Cmd* h = firstCmd;
        int  j = 0;

        while (h && j < i) {
            h = h->next;
            j++;
        }
        return h;
    }

    Cmd* SimpleCLI::getCmd(String cmdName) {
        return getNextCmd(firstCmd, cmdName);
    }

    Cmd* SimpleCLI::getNextCmd(Cmd* begin, String cmdName) {
        Cmd* h = begin;

        while (h) {
            if (equals(cmdName.c_str(), h->getName().c_str()) >= 0) return h;

            h = h->next;
        }
        return h;
    }

    Cmd* SimpleCLI::getCmd(const char* cmdName) {
        return getNextCmd(firstCmd, cmdName);
    }

    Cmd* SimpleCLI::getNextCmd(Cmd* begin, const char* cmdName) {
        Cmd* h = begin;

        while (h) {
            if (equals(cmdName, h->getName().c_str()) >= 0) return h;

            h = h->next;
        }
        return h;
    }

    void SimpleCLI::addCmd(Cmd* newCmd) {
        if (lastCmd) lastCmd->next = newCmd;

        if (!firstCmd) firstCmd = newCmd;
        lastCmd = newCmd;
        cmdNum++;
    }

    void SimpleCLI::addCmd(Command* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void SimpleCLI::addCmd(BoundlessCmd* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void SimpleCLI::addCmd(EmptyCmd* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void SimpleCLI::addCmd(SingleArgCmd* newCmd) {
        addCmd(static_cast<Cmd*>(newCmd));
    }

    void SimpleCLI::setCaseSensetive() {
        caseSensetive = true;
    }

    String SimpleCLI::toString() {
        String s;
        Cmd  * h = firstCmd;

        while (h != NULL) {
            s += h->toString();
            s += '\r';
            s += '\n';
            h  = h->next;
        }

        return s;
    }

    String SimpleCLI::readCmdName(String& input) {
        char   c;
        String cmdName;

        while (input.length() > 0 && c != ' ') {
            c = input.charAt(0);
            input.remove(0, 1);

            if (c != ' ') cmdName += c;
        }

        return cmdName;
    }

    String SimpleCLI::getNextArg(String& input) {
        String arg;
        char   c;
        bool   escaped  = false;
        bool   inQuotes = false;

        while (input.length() > 0) {
            c = input.charAt(0);
            input.remove(0, 1);

            // escape character BACKSLASH
            if (c == '\\') {
                escaped = !escaped;

                if (escaped) continue;
            }

            // Quotes
            else if ((c == '"') && !escaped) {
                inQuotes = !inQuotes;
                continue;
            }

            if (!escaped && !inQuotes && ((c == ' ') || (c == '\r') || (c == '\n'))) {
                return arg;
            }

            // add chars to temp-string
            else {
                arg    += c;
                escaped = false;
            }
        }

        return arg;
    }
}