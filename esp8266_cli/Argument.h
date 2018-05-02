#ifndef Argument_h
#define Argument_h

#include "Arg.h"

class Argument: public Arg {
  public:
    Argument(const char* name, const char* defaultValue, bool required) {
      // copy name
      if (name) {
        int strLen = strlen(name);
        Argument::name = new char[strLen + 1];
        strcpy(Argument::name, name);
        Argument::name[strLen] = '\0';
      } else {
        Argument::name = new char[1];
        Argument::name[0] = '\0';
      }

      // copy defaultValue
      if (defaultValue) {
        int strLen = strlen(defaultValue);
        Argument::defaultValue = new char[strLen + 1];
        strcpy(Argument::defaultValue, defaultValue);
        Argument::defaultValue[strLen] = '\0';
      } else {
        Argument::defaultValue = new char[1];
        Argument::defaultValue[0] = '\0';
      }

      // set required
      Argument::required = required;

      // load defaults
      reset();
    }

    Argument(String name, String defaultValue, bool required) {
      int strLen;

      strLen = name.length() + 1;
      Argument::name = new char[strLen];
      name.toCharArray(Argument::name, strLen);

      strLen = defaultValue.length() + 1;
      Argument::defaultValue = new char[strLen];
      defaultValue.toCharArray(Argument::defaultValue, strLen);

      // set required
      Argument::required = required;

      // load defaults
      reset();
    }

    ~Argument() {
      delete name;
      delete defaultValue;
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      equalsKeyword(name, Argument::name);
    }

    void setValue(String value) {
      if (Argument::value) delete Argument::value;

      int strLen = value.length() + 1;
      Argument::value = new char[strLen];
      value.toCharArray(Argument::value, strLen);

      set = true;
    }

    void reset() {
      if (value) delete value;

      int strLen = strlen(defaultValue);
      value = new char[strLen + 1];
      strcpy(value, defaultValue);
      value[strLen] = '\0';

      set = false;
    }
};

#endif

