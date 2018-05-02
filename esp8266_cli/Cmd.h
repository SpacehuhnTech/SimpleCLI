#ifndef Cmd_h
#define Cmd_h

#include <stddef.h>
#include <functional>

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

    String getName() {
      return String(name);
    }

    const char* getNamePtr() {
      return name;
    }

    virtual bool equalsName(const char* name) = 0;
    
    uint8_t equals(String name, int argNum, Arg* firstArg) {
      if (!equalsName(name.c_str())) return WRONG_NAME;
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

    bool addArg(Arg* newArg) {
      if(getArg(newArg->getName()) == NULL){
        newArg->next = firstArg;
        firstArg = newArg;
        argNum++;
        return true;
      }
      return false;
    }

    bool addArg(Argument* newArg) {
      return addArg(static_cast<Arg*>(newArg));
    }

    bool addArg(Argument_P* newArg) {
      if(getArg(newArg->getNamePtr()) == NULL){
        newArg->next = firstArg;
        firstArg = static_cast<Arg*>(newArg);
        argNum++;
        return true;
      }
      return false;
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
        if (h->equals(name.c_str()))
          return h;
        h = h->next;
      }
      return NULL;
    }

    Arg* getArg_P(const char* name) {
      Arg* h = firstArg;
      while (h) {
        if (name == h->getNamePtr())
          return h;
        h = h->next;
      }
      return NULL;
    }

    bool hasArg(String name) {
      return getArg(name) != NULL;
    }
    
    bool hasArg_P(const char* name) {
      return getArg_P(name) != NULL;
    }
    
    bool has(String name) {
      Arg* h = getArg(name);
      return h ? h->isSet() : false;
    }

    bool has_P(const char* name) {
      Arg* h = getArg_P(name);
      return h ? h->isSet() : false;
    }

    String value(String name) {
      Arg* arg = getArg(name);
      return arg ? arg->getValue() : String();
    }
    
    String value_P(const char* name) {
      Arg* arg = getArg_P(name);
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
    void (*runFnct)(Cmd*) = NULL;
    void (*errorFnct)(uint8_t) = NULL;
    int argNum = 0;

    bool equalsKeyword(const char* str, const char* keyword) {
      if (!str) return false;
      if (!keyword) return false;

      int lenStr = strlen(str);
      int lenKeyword = strlen(keyword);

      // string can't be longer than keyword (but can be smaller because of '/' and ',')
      if (lenStr > lenKeyword)
        return false;

      if (lenStr == lenKeyword)
        return strcmp(str, keyword) == 0;

      int a = 0;
      int b = 0;
      bool result = true;

      while (a < lenStr && b < lenKeyword) {
        if (keyword[b] == '/') {
          b++;
        } else if (keyword[b] == ',') {
          b++;
          a = 0;
        }

        if (tolower(str[a]) != tolower(keyword[b])) {
          result = false;
        }

        // fast forward to next comma
        if ((a == lenStr && !result) || !result) {
          while (b < lenKeyword && keyword[b] != ',') b++;
          result = true;
        } else {
          a++;
          b++;
        }
      }
      // comparison correct AND string checked until the end AND keyword checked until the end
      result = result && a == lenStr && (keyword[b] == ',' || keyword[b] == '/' || keyword[b] == '\0');
      return result;
    }
};

#endif

