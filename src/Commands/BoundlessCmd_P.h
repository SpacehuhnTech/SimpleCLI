#ifndef BoundlessCmd_P_h
#define BoundlessCmd_P_h

#include "Cmd.h"

namespace simpleCLI {
    class BoundlessCmd_P : public Cmd {
        public:
            BoundlessCmd_P(const char* name, void(*runFnct)(Cmd*));
            ~BoundlessCmd_P();

            String getName();
            void reset();
            bool parse(String arg, String value);
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
            int args         = 0;
            Arg* firstArg    = NULL;
            Arg* lastArg     = NULL;
    };
}

#endif // ifndef BoundlessCmd_P_h