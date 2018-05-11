#ifndef Arduino_CLI_h
#define Arduino_CLI_h

#include "Arduino.h"
#include "helper_functions.h"
#include "Arguments/Arg.h"

#include "Commands/Cmd.h"
#include "Commands/BoundlessCmd.h"
#include "Commands/Command.h"
#include "Commands/EmptyCmd.h"

#include "Commands/BoundlessCmd_P.h"
#include "Commands/Command_P.h"
#include "Commands/EmptyCmd_P.h"

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
            Cmd* getCommand(int i);
            Cmd* getCommand(String cmdName);
            Cmd* getCommand(const char* cmdName);
            void addCommand(Cmd* newCmd);

            void addCommand(Command* newCmd);
            void addCommand(Command_P* newCmd);
            void addCommand(BoundlessCmd* newCmd);
            void addCommand(BoundlessCmd_P* newCmd);
            void addCommand(EmptyCmd* newCmd);
            void addCommand(EmptyCmd_P* newCmd);

            void setCaseSensetive();

        private:
            int cmdNum    = 0;
            Cmd* firstCmd = NULL;
            Cmd* lastCmd  = NULL;
    };
}
#endif // ifndef CommandParser_h