#ifndef EmptyCmd_P_h
#define EmptyCmd_P_h

#include "Cmd.h"

namespace arduino_cli {
    class EmptyCmd_P : public Cmd {
        public:
            EmptyCmd_P(const char* name, void(*runFnct)(Cmd*));
            ~EmptyCmd_P();

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
#endif // ifndef EmptyCmd_P_h