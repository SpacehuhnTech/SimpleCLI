#ifndef Arg_h
#define Arg_h

#include "Arduino.h"
extern "C" {
  #include "user_interface.h"
}

extern bool equalsKeyword(const char* str, const char* keyword);

class Arg {
  public:
    Arg* next = NULL;

    virtual ~Arg() = default;

    virtual void setValue(String value) = 0;
    virtual void reset() = 0;
    virtual bool equals(String name) = 0;
    virtual bool equals(const char* name) = 0;
    
    String getName() {
      return String(name);
    }

    String getValue() {
      return String(value);
    }

    bool isSet() {
      return set;
    }

    bool isRequired() {
      return required;
    }

  protected:
    char* name = NULL;
    char* defaultValue = NULL;
    char* value = NULL;
    bool set = false;
    bool required = false;
};

#endif

