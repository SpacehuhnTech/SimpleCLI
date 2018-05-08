#ifndef BoundlessCmd_h
#define BoundlessCmd_h

#include "Cmd.h"

namespace arduino_cli {
    class BoundlessCmd : public Cmd {
        public:
            BoundlessCmd(const char *name, void(*runFnct)(Cmd *));
            BoundlessCmd(String name, void(*runFnct)(Cmd *));
            ~BoundlessCmd();

            String getName();
            void reset();
            bool parse(String arg, String value);
            int argNum();
            Arg* getArg(int i);
            Arg* getArg(const char *name);
            Arg* getArg(String name);
            bool isSet(int i);
            bool isSet(const char *name);
            bool isSet(String name);
            String value(int i);
            String value(const char *name);
            String value(String name);
            bool isSet();

        private:
            char *name    = NULL;
            int args      = 0;
            Arg *firstArg = NULL;
            Arg *lastArg  = NULL;
    };
}
#endif // ifndef BoundlessCmd_h