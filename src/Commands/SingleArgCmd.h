#ifndef BoundlessCmd_h
#define BoundlessCmd_h

#include "Cmd.h"

namespace arduino_cli {
    class SingleArgCmd : public Cmd {
        public:
            SingleArgCmd(const char* name, void(*runFnct)(Cmd *));
            SingleArgCmd(String name, void(*runFnct)(Cmd *));
            ~SingleArgCmd();

            String getName();
            void reset();
            bool parse(String argName, String argValue);
            int argNum();
            Arg* getArg(int i);
            Arg* getArg(const char* name);
            Arg* getArg(String name);
            bool isSet(int i);
            bool isSet(const char* name);
            bool isSet(String name);
            String value(int i);
            String value(const char* name);
            String value(String name);
            bool isSet();

        private:
            char* name = NULL;
            Arg* arg   = NULL;
    };
}
#endif // ifndef BoundlessCmd_h