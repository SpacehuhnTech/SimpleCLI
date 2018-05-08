#ifndef EmptyCmd_h
#define EmptyCmd_h

#include "Cmd.h"

namespace arduino_cli {
    class EmptyCmd : public Cmd {
        public:
            EmptyCmd(const char *name, void(*runFnct)(Cmd *));
            EmptyCmd(String name, void(*runFnct)(Cmd *));
            ~EmptyCmd();

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
            char *name = NULL;
    };
}
#endif // ifndef EmptyCmd_h