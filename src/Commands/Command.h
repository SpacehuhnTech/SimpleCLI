#ifndef Command_h
#define Command_h

#include "Cmd.h"

namespace arduino_cli {
    class Command : public Cmd {
        public:
            Command(const char *name, void(*runFnct)(Cmd *));
            Command(String name, void(*runFnct)(Cmd *));
            ~Command();

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

            void addArg(Arg *newArg);
            void addArg(ReqArg *newArg);
            void addArg(OptArg *newArg);
            void addArg(EmptyArg *newArg);
            void addArg(AnonymReqArg *newArg);
            void addArg(AnonymOptArg *newArg);
            void addArg(TemplateReqArg *newArg);
            void addArg(TemplateOptArg *newArg);

            bool isSet();

#if defined(ESP8266) || defined(ESP32)
            void addArg(ReqArg_P *newArg);
            void addArg(OptArg_P *newArg);
            void addArg(EmptyArg_P *newArg);
            void addArg(AnonymOptArg_P *newArg);
            void addArg(TemplateReqArg_P *newArg);
            void addArg(TemplateOptArg_P *newArg);
#endif // if defined(ESP8266) || defined(ESP32)

        private:
            char *name    = NULL;
            int args      = 0;
            Arg *firstArg = NULL;
            Arg *lastArg  = NULL;
    };
}
#endif // ifndef Command_h