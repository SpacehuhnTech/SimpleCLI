#ifndef Cmd_h
#define Cmd_h

#include "cli_helper.h"

#include "Arg.h"

#include "ReqArg.h"
#include "ReqArg_P.h"
#include "OptArg.h"
#include "OptArg_P.h"
#include "EmptyArg.h"
#include "EmptyArg_P.h"
#include "AnonymReqArg.h"
#include "AnonymOptArg.h"
#include "AnonymOptArg_P.h"
#include "TemplateReqArg.h"
#include "TemplateReqArg_P.h"
#include "TemplateOptArg.h"
#include "TemplateOptArg_P.h"

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

