#ifndef OptArg_h
#define OptArg_h

#include "Arg.h"

class OptArg: public Arg {
  public:
    OptArg(const char* name, const char* defaultValue) {
      if (name) {
        int strLen = strlen(name);
        OptArg::name = new char[strLen + 1];
        strcpy_P(OptArg::name, name);
        OptArg::name[strLen] = '\0';
      }

      if (defaultValue) {
        int strLen = strlen(defaultValue);
        OptArg::defaultValue = new char[strLen + 1];
        strcpy_P(OptArg::defaultValue, defaultValue);
        OptArg::defaultValue[strLen] = '\0';
      }

      reset();
    }

    OptArg(String name, String defaultValue) {
      int strLen;

      strLen = name.length() + 1;
      OptArg::name = new char[strLen];
      name.toCharArray(OptArg::name, strLen);

      strLen = defaultValue.length() + 1;
      OptArg::defaultValue = new char[strLen];
      defaultValue.toCharArray(OptArg::defaultValue, strLen);

      reset();
    }

    ~OptArg() {
      if (name) delete name;
      if (defaultValue) delete defaultValue;
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      if (!name) return false;
      if (!OptArg::name) return false;
      if (name == OptArg::name) return true;

      int strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      return equalsKeyword(tmpName, OptArg::name);
    }

    bool equals(String name) {
      return equalsKeyword(name.c_str(), OptArg::name);
    }

    void setValue(String value) {
      if (value.length() > 0) {
        if (OptArg::value) delete OptArg::value;

        int strLen = value.length() + 1;
        OptArg::value = new char[strLen];
        value.toCharArray(OptArg::value, strLen);

        set = true;
      }
    }

    void reset() {
      if (value) delete value;

      if (defaultValue) {
        int strLen = strlen(defaultValue);
        value = new char[strLen + 1];
        strcpy(value, defaultValue);
        value[strLen] = '\0';
      }

      Arg::reset();
    }

    String getName() {
      return name ? String(name) : String();
    }

    String getValue() {
      return value ? String(value) : String();
    }

    bool isRequired() {
      return false;
    }

  private:
    char* name = NULL;
    char* defaultValue = NULL;
    char* value = NULL;
};

#endif

