#ifndef Command_P_h
#define Command_P_h

#include "Cmd.h"

namespace simpleCLI {
    class Command_P : public Cmd {
        public:
            Command_P(const char* name, void(*runFnct)(Cmd*));
            ~Command_P();

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

            void addArg(ReqArg_P* newArg);
            void addArg(OptArg_P* newArg);
            void addArg(EmptyArg_P* newArg);
            void addArg(AnonymOptArg_P* newArg);
            void addArg(TemplateReqArg_P* newArg);
            void addArg(TemplateOptArg_P* newArg);

            bool isSet();

            String toString();

        private:
            const char* name = NULL;
            int args         = 0;
            Arg* firstArg    = NULL;
            Arg* lastArg     = NULL;
    };
}
#endif // ifndef Command_P_h