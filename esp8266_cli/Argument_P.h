#ifndef Argument_P_h
#define Argument_P_h

#include "Arg.h"

class Argument_P: public Arg {
  public:
    Argument_P(const char* name, const char* defaultValue, bool required) {
      Argument_P::name = const_cast<char*>(name);
      if(defaultValue) Argument_P::defaultValue = const_cast<char*>(defaultValue);
      Argument_P::required = required;

      // load defaults
      reset();
    }

    ~Argument_P() {
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      int tmpNameLen = strlen_P(Argument_P::name);
      char* tmpName = new char[tmpNameLen + 1];
      strcpy_P(tmpName, Argument_P::name);
      tmpName[tmpNameLen] = '\0';

      bool res = Arg::equalsKeyword(name, tmpName);
      delete tmpName;
      return res;
    }

    void setValue(String value) {
      if (Argument_P::value) delete Argument_P::value;

      int strLen = value.length() + 1;
      Argument_P::value = new char[strLen];
      value.toCharArray(Argument_P::value, strLen);

      set = true;
    }

    void reset() {
      if (value) delete value;
      
      if (defaultValue){
        int strLen = strlen_P(defaultValue);
        value = new char[strLen + 1];
        strcpy_P(value, defaultValue);
        value[strLen] = '\0';
      }
      
      set = false;
    }
};

#endif

