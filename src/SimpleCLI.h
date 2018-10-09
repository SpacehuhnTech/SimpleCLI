#ifndef SimpleCLI_h
#define SimpleCLI_h

#include "Arduino.h"
#include "helper_functions.h"
#include "Arguments/Arg.h"

#include "Commands/Cmd.h"
#include "Commands/BoundlessCmd.h"
#include "Commands/Command.h"
#include "Commands/EmptyCmd.h"
#include "Commands/SingleArgCmd.h"

namespace simplecli {
    class SimpleCLI {
        public:
            void (* onNotFound)(String cmdName) = NULL;

            SimpleCLI();
            ~SimpleCLI();

            void parse(String input);

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

            void setCaseSensetive();

            String toString();

            template<typename T>
            void print(T out) {
                Cmd* h = firstCmd;

                while (h != NULL) {
                    String s = h->toString();
                    out->println(s);
                    h = h->next;
                }
            }

        private:
            int cmdNum    = 0;
            Cmd* firstCmd = NULL;
            Cmd* lastCmd  = NULL;

            void parseLines(String& input);
            void parseLine(String& input);
            String readCmdName(String& input);
            String getNextArg(String& input);
    };
}
#endif // ifndef CommandParser_h