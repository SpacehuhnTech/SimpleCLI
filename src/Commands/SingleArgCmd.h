#ifndef SingleArgCmd_h
#define SingleArgCmd_h

#include "Cmd.h"

namespace simpleCLI {
    class SingleArgCmd : public Cmd {
        public:
            SingleArgCmd(const char* name, void(*runFnct)(Cmd*));
            SingleArgCmd(String name, void(*runFnct)(Cmd*));
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

            String getValue(int i);
            String getValue(const char* name);
            String getValue(String name);

            bool isSet();

            String toString();

        private:
            char* name  = NULL;
            char* value = NULL;
    };
}
#endif // ifndef SingleArgCmd_h