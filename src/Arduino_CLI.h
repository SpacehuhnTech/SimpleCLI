#ifndef Arduino_CLI_h
#define Arduino_CLI_h

#include "Arduino.h"
#include "helper_functions.h"
#include "Arguments/Arg.h"

#include "Commands/Cmd.h"
#include "Commands/BoundlessCmd.h"
#include "Commands/Command.h"
#include "Commands/EmptyCmd.h"
#include "Commands/SingleArgCmd.h"

#include "Commands/BoundlessCmd_P.h"
#include "Commands/Command_P.h"
#include "Commands/EmptyCmd_P.h"
#include "Commands/SingleArgCmd_P.h"

namespace arduino_cli {
    class Arduino_CLI {
        public:
            void (*onNotFound)(String cmdName) = NULL;

            Arduino_CLI();
            ~Arduino_CLI();

            void parse(String input);
            void parse(const char* input);
            void parseLines(const char* str, int strLen);
            void parseLine(const char* str, int strLen);

            Cmd* getCmd(int i);
            Cmd* getCmd(String cmdName);
            Cmd* getCmd(const char* cmdName);

            Cmd* getNextCmd(Cmd* begin, String cmdName);
            Cmd* getNextCmd(Cmd* begin, const char* cmdName);

            void addCmd(Cmd* newCmd);
            void addCmd(Command* newCmd);
            void addCmd(BoundlessCmd* newCmd);
            void addCmd(EmptyCmd* newCmd);
            void addCmd(SingleArgCmd* newCmd);

            void addCmd(Command_P* newCmd);
            void addCmd(BoundlessCmd_P* newCmd);
            void addCmd(EmptyCmd_P* newCmd);
            void addCmd(SingleArgCmd_P* newCmd);

            void setCaseSensetive();

            String toString();

        private:
            int cmdNum    = 0;
            Cmd* firstCmd = NULL;
            Cmd* lastCmd  = NULL;
    };
}
#endif // ifndef CommandParser_h