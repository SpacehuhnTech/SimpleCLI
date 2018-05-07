#ifndef AnonymOptArg_P_h
#define AnonymOptArg_P_h

#include "Arg.h"

class AnonymOptArg_P: public Arg {
  public:
    AnonymOptArg_P(const char* defaultValue) {
      AnonymOptArg_P::defaultValue = defaultValue;
      reset();
    }

    ~AnonymOptArg_P() {
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      return strlen_P(name) == 0;
    }

    bool equals(String name) {
      return name.length() == 0;
    }

    void setValue(String value) {
      if (value.length() > 0) {
        if (AnonymOptArg_P::value) delete AnonymOptArg_P::value;

        int strLen = value.length() + 1;
        AnonymOptArg_P::value = new char[strLen];
        value.toCharArray(AnonymOptArg_P::value, strLen);

        set = true;
      }
    }

    void reset() {
      if (value){
        delete value;
        value = NULL;
      }

      if (defaultValue) {
        int strLen = strlen_P(defaultValue);
        value = new char[strLen + 1];
        strcpy_P(value, defaultValue);
        value[strLen] = '\0';
      }

      Arg::reset();
    }

    String getValue() {
      return value ? String(value) : String();
    }

    bool isRequired() {
      return false;
    }

  private:
    char* value = NULL;
    const char* defaultValue = NULL;
};

#endif
