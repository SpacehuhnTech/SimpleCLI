#ifndef Cmd_h
#define Cmd_h

#include "Arduino.h"
extern "C" {
  #include "user_interface.h"
}

extern bool equalsKeyword(const char* str, const char* keyword);

class Cmd {
  public:
    Cmd* next = NULL;

    virtual ~Cmd() = default;

    static const uint8_t OK = 0;
    static const uint8_t WRONG_NAME = 1;
    static const uint8_t TOO_MANY_ARGS = 2;
    static const uint8_t MISSING_ARGS = 3;
    static const uint8_t DUPLICATE_ARG = 4;
    static const uint8_t INVALID_ARG = 5;

    virtual uint8_t equals(const char* name, int argNum, Arg* firstArg) = 0;
    virtual uint8_t equals(String name, int argNum, Arg* firstArg) = 0;

    int args(){
      return argNum;
    }
    
    String getName() {
      return String(name);
    }

    const char* getNamePtr() {
      return name;
    }

    bool addArg(Arg* newArg) {
      if(getArg(newArg->getName()) == NULL){
        if(lastArg) lastArg->next = newArg;
        if(!firstArg) firstArg = newArg;
        lastArg = newArg;
        argNum++;
        return true;
      }
      return false;
    }

    bool addArg(Argument* newArg) {
      return addArg(static_cast<Arg*>(newArg));
    }

    bool addArg(Argument_P* newArg) {
      return addArg(static_cast<Arg*>(newArg));
    }

    bool addArg(String name, String defaultValue, bool required) {
      return addArg(new Argument(name, defaultValue, required));
    }

    bool addArg_P(const char* name, const char* defaultValue, bool required) {
      return addArg(new Argument_P(name, defaultValue, required));
    }

    bool addOptArg(String name, String defaultValue) {
      return addArg(name, defaultValue, false);
    }

    bool addOptArg_P(const char* name, const char* defaultValue) {
      return addArg_P(name, defaultValue, false);
    }

    bool addReqArg(String name, String defaultValue) {
      return addArg(name, defaultValue, true);
    }

    bool addReqArg_P(const char* name, const char* defaultValue) {
      return addArg_P(name, defaultValue, true);
    }
    
    Arg* getArg(String name) {
      Arg* h = firstArg;
      while (h) {
        if (h->equals(name))
          return h;
        h = h->next;
      }
      return NULL;
    }

    Arg* getArg(const char* name) {
      Arg* h = firstArg;
      while (h) {
        if (h->equals(name))
          return h;
        h = h->next;
      }
      return NULL;
    }
    
    Arg* getArg(int i) {
      Arg* h = firstArg;
      int j=0;
      while (h && j<i) {
        h = h->next;
        j++;
      }
      return h;
    }
    
    bool hasArg(String name) {
      return getArg(name) != NULL;
    }
    
    bool hasArg(const char* name) {
      return getArg(name) != NULL;
    }

    bool hasArg(int i) {
      return getArg(i) != NULL;
    }
    
    bool has(String name) {
      Arg* h = getArg(name);
      return h ? h->isSet() : false;
    }

    bool has(const char* name) {
      Arg* h = getArg(name);
      return h ? h->isSet() : false;
    }

    bool has(int i) {
      Arg* h = getArg(i);
      return h ? h->isSet() : false;
    }

    String value(String name) {
      Arg* arg = getArg(name);
      return arg ? arg->getValue() : String();
    }
    
    String value(const char* name) {
      Arg* arg = getArg(name);
      return arg ? arg->getValue() : String();
    }

    String value(int i) {
      Arg* arg = getArg(i);
      return arg ? arg->getValue() : String();
    }
    
    void resetArguments() {
      Arg* h = firstArg;
      while (h) {
        h->reset();
        h = h->next;
      }
    }

    bool run(Cmd* cmd) {
      if (runFnct) {
        runFnct(cmd);
        return true;
      }
      return false;
    }

    bool error(uint8_t error) {
      if (errorFnct) {
        errorFnct(error);
        return true;
      }
      return false;
    }
    
  protected:
    char* name = NULL;
    Arg* firstArg = NULL;
    Arg* lastArg = NULL;
    void (*runFnct)(Cmd*) = NULL;
    void (*errorFnct)(uint8_t) = NULL;
    int argNum = 0;

    uint8_t parse(int argNum, Arg* firstArg) {
      if (argNum > Cmd::argNum) return TOO_MANY_ARGS;

      resetArguments();

      // check and set argument values
      Arg* h = firstArg;
      Arg* tmp;
      while (h != NULL) {
        tmp = getArg(h->getName());

        if (tmp) {
          if (!tmp->isSet()) {
            tmp->setValue(h->getValue());
          } else {
            return DUPLICATE_ARG; // argument twice in the list
          }
        } else {
          return INVALID_ARG; // argument not found
        }

        h = h->next;
      }

      // check for all required arguments
      h = Cmd::firstArg;
      while (h != NULL) {
        if (h->isRequired() && !h->isSet())
          return MISSING_ARGS;
        h = h->next;
      }

      return OK;
    }
};

#endif

