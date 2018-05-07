#ifndef Cmd_h
#define Cmd_h

#include "cli_helper.h"

#include "Arguments/Arg.h"

#include "Arguments/ReqArg.h"
#include "Arguments/ReqArg_P.h"
#include "Arguments/OptArg.h"
#include "Arguments/OptArg_P.h"
#include "Arguments/EmptyArg.h"
#include "Arguments/EmptyArg_P.h"
#include "Arguments/AnonymReqArg.h"
#include "Arguments/AnonymOptArg.h"
#include "Arguments/AnonymOptArg_P.h"
#include "Arguments/TemplateReqArg.h"
#include "Arguments/TemplateReqArg_P.h"
#include "Arguments/TemplateOptArg.h"
#include "Arguments/TemplateOptArg_P.h"

class Cmd {
  public:
    Cmd* next = NULL;

    virtual ~Cmd() = default;

    virtual String getName() = 0;
    virtual void reset() = 0;
    virtual bool parse(String arg, String value) = 0;
    virtual int argNum() = 0;

    virtual Arg* getArg(int i) = 0;
    virtual Arg* getArg(const char* name) = 0;
    virtual Arg* getArg(String name) = 0;

    virtual bool isSet(int i) = 0;
    virtual bool isSet(const char* name) = 0;
    virtual bool isSet(String name) = 0;

    virtual String value(int i) = 0;
    virtual String value(const char* name) = 0;
    virtual String value(String name) = 0;

    virtual bool isSet() = 0;

    bool run(Cmd* cmd) {
      if (runFnct) {
        runFnct(cmd);
        return true;
      }
      return false;
    }
  protected:
    void (*runFnct)(Cmd*) = NULL;
};

#endif
