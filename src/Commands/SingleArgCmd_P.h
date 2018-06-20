#ifndef SingleArgCmd_P_h
#define SingleArgCmd_P_h

#include "Cmd.h"

namespace simpleCLI {
    class SingleArgCmd_P : public Cmd {
        public:
            SingleArgCmd_P(const char* name, void(*runFnct)(Cmd*));
            ~SingleArgCmd_P();

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
            const char* name = NULL;
            char* value      = NULL;
    };
}

#endif // ifndef SingleArgCmd_P