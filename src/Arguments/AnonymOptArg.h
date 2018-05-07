#ifndef AnonymOptArg_h
#define AnonymOptArg_h

#include "Arg.h"

class AnonymOptArg: public Arg {
  public:
    AnonymOptArg(const char* defaultValue) {
      if (defaultValue) {
        int strLen = strlen(defaultValue);
        AnonymOptArg::defaultValue = new char[strLen + 1];
        strcpy(AnonymOptArg::defaultValue, defaultValue);
        AnonymOptArg::defaultValue[strLen] = '\0';
      }

      reset();
    }

    AnonymOptArg(String defaultValue) {
      int strLen = defaultValue.length() + 1;
      AnonymOptArg::defaultValue = new char[strLen];
      defaultValue.toCharArray(AnonymOptArg::defaultValue, strLen);

      reset();
    }

    ~AnonymOptArg() {
      if (defaultValue) delete defaultValue;
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      return strlen(name) == 0;
    }

    bool equals(String name) {
      return name.length() == 0;
    }

    void setValue(String value) {
      if (value.length() > 0) {
        if (AnonymOptArg::value) delete AnonymOptArg::value;

        int strLen = value.length() + 1;
        AnonymOptArg::value = new char[strLen];
        value.toCharArray(AnonymOptArg::value, strLen);

        set = true;
      }
    }

    void reset() {
      if (value){
        delete value;
        value = NULL;
      }

      if (defaultValue) {
        int strLen = strlen(defaultValue);
        value = new char[strLen + 1];
        strcpy(value, defaultValue);
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
    char* defaultValue = NULL;
};

#endif
