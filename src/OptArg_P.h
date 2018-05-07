#ifndef OptArg_P_h
#define OptArg_P_h

#include "Arg.h"

class OptArg_P: public Arg {
  public:
    OptArg_P(const char* name, const char* defaultValue) {
      OptArg_P::name = name;
      OptArg_P::defaultValue = defaultValue;

      reset();
    }

    ~OptArg_P() {
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      if (!name) return false;
      if (!OptArg_P::name) return false;
      if (name == OptArg_P::name) return true;

      int strLen;
      strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      strLen = strlen_P(OptArg_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, OptArg_P::name);
      tmpKeyword[strLen] = '\0';

      return cli_helper::equals(tmpName, tmpKeyword) >= 0;
    }

    bool equals(String name) {
      if (!OptArg_P::name) return false;

      int strLen = strlen_P(OptArg_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, OptArg_P::name);
      tmpKeyword[strLen] = '\0';

      return cli_helper::equals(name.c_str(), tmpKeyword) >= 0;
    }

    void setValue(String value) {
      if (value.length() > 0) {
        if (OptArg_P::value) delete OptArg_P::value;

        int strLen = value.length() + 1;
        OptArg_P::value = new char[strLen];
        value.toCharArray(OptArg_P::value, strLen);

        set = true;
      }
    }

    void reset() {
      if (value) delete value;

      int strLen = strlen_P(defaultValue);
      value = new char[strLen + 1];
      strcpy_P(value, defaultValue);
      value[strLen] = '\0';

      Arg::reset();
    }

    String getName() {
      if (!name) return String();

      int strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      return String(tmpName);
    }

    String getValue() {
      return value ? String(value) : String();
    }
    bool isRequired() {
      return false;
    }

  private:
    const char* name = NULL;
    const char* defaultValue = NULL;
    char* value = NULL;
};

#endif
