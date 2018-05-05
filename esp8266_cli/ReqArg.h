#ifndef ReqArg_h
#define ReqArg_h

#include "Arg.h"

class ReqArg: public Arg {
  public:
    ReqArg(const char* name) {
      // copy name
      if (name) {
        int strLen = strlen(name);
        ReqArg::name = new char[strLen + 1];
        strcpy_P(ReqArg::name, name);
        ReqArg::name[strLen] = '\0';
      }

      reset();
    }

    ReqArg(String name) {
      int strLen = name.length() + 1;
      ReqArg::name = new char[strLen];
      name.toCharArray(ReqArg::name, strLen);

      reset();
    }

    ~ReqArg() {
      if (name) delete name;
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      if (!name) return false;
      if (!ReqArg::name) return false;
      if (name == ReqArg::name) return true;

      int strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      return equalsKeyword(tmpName, ReqArg::name);
    }

    bool equals(String name) {
      return equalsKeyword(name.c_str(), ReqArg::name);
    }

    void setValue(String value) {
      if (value.length() > 0) {
        if (ReqArg::value) delete ReqArg::value;

        int strLen = value.length() + 1;
        ReqArg::value = new char[strLen];
        value.toCharArray(ReqArg::value, strLen);

        set = true;
      }
    }

    void reset() {
      if (value) delete value;

      Arg::reset();
    }

    String getName() {
      return name ? String(name) : String();
    }

    String getValue() {
      return value ? String(value) : String();
    }

    bool isRequired() {
      return true;
    }

  private:
    char* name = NULL;
    char* value = NULL;
};

#endif

