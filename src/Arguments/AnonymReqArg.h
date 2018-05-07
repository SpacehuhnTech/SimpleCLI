#ifndef AnonymReqArg_h
#define AnonymReqArg_h

#include "Arg.h"

class AnonymReqArg: public Arg {
  public:
    AnonymReqArg() {
      reset();
    }

    ~AnonymReqArg() {
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
        if (AnonymReqArg::value) delete AnonymReqArg::value;

        int strLen = value.length() + 1;
        AnonymReqArg::value = new char[strLen];
        value.toCharArray(AnonymReqArg::value, strLen);

        set = true;
      }
    }

    void reset() {
      if (value){
        delete value;
        value = NULL;
      }

      Arg::reset();
    }

    String getValue() {
      return value ? String(value) : String();
    }

    bool isRequired() {
      return true;
    }

  private:
    char* value = NULL;
};

#endif
