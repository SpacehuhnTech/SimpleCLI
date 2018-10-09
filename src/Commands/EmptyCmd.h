#ifndef EmptyCmd_h
#define EmptyCmd_h

#include "Cmd.h"

namespace simplecli {
    class EmptyCmd : public Cmd {
        public:
            EmptyCmd(const char* name, CmdRunFunction);
            ~EmptyCmd();

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
    };
}
#endif // ifndef EmptyCmd_h