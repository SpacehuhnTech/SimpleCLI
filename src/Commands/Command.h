#ifndef Command_h
#define Command_h

#include "Cmd.h"

namespace simplecli {
    class Command : public Cmd {
        public:
            Command(const char* name, CmdRunFunction);
            ~Command();

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

            void addArg(Arg* newArg);
            void addArg(ReqArg* newArg);
            void addArg(OptArg* newArg);
            void addArg(EmptyArg* newArg);
            void addArg(AnonymReqArg* newArg);
            void addArg(AnonymOptArg* newArg);
            void addArg(TemplateReqArg* newArg);
            void addArg(TemplateOptArg* newArg);

            bool isSet();

            String toString();

        private:
            const char* name = NULL;
            int args         = 0;
            Arg* firstArg    = NULL;
            Arg* lastArg     = NULL;
    };
}
#endif // ifndef Command_h