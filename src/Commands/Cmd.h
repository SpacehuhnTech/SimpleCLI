#ifndef Cmd_h
#define Cmd_h

#include "Arduino.h"
#include "helper_functions.h"

#include "Arguments/Arg.h"
#include "Arguments/ReqArg.h"
#include "Arguments/OptArg.h"
#include "Arguments/EmptyArg.h"
#include "Arguments/AnonymReqArg.h"
#include "Arguments/AnonymOptArg.h"
#include "Arguments/TemplateReqArg.h"
#include "Arguments/TemplateOptArg.h"

#include "Arguments/OptArg_P.h"
#include "Arguments/ReqArg_P.h"
#include "Arguments/TemplateReqArg_P.h"
#include "Arguments/TemplateOptArg_P.h"

namespace simpleCLI {
    class Cmd {
        public:
            Cmd* next = NULL;

            virtual ~Cmd() = default;

            virtual String getName()                              = 0;
            virtual void   reset()                                = 0;
            virtual bool   parse(String argName, String argValue) = 0;
            virtual int    argNum()                               = 0;

            virtual Arg* getArg(int i)            = 0;
            virtual Arg* getArg(const char* name) = 0;
            virtual Arg* getArg(String name)      = 0;

            virtual bool   isSet(int i)            = 0;
            virtual bool   isSet(const char* name) = 0;
            virtual bool   isSet(String name)      = 0;

            virtual String getValue(int i)            = 0;
            virtual String getValue(const char* name) = 0;
            virtual String getValue(String name)      = 0;

            virtual bool   isSet() = 0;

            virtual String toString() = 0;

            virtual inline bool run(Cmd* cmd) {
                if (runFnct) runFnct(cmd);
                return runFnct;
            }

        protected:
            void (* runFnct)(Cmd*) = NULL;
    };
}

#endif // ifndef Cmd_h