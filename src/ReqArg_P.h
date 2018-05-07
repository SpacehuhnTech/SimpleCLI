#ifndef ReqArg_P_h
#define ReqArg_P_h

#include "Arg.h"

class ReqArg_P: public Arg {
  public:
    ReqArg_P(const char* name) {
      ReqArg_P::name = name;
    }

    ~ReqArg_P() {
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      if (!name) return false;
      if (!ReqArg_P::name) return false;
      if (name == ReqArg_P::name) return true;

      int strLen;
      strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      strLen = strlen_P(ReqArg_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, ReqArg_P::name);
      tmpKeyword[strLen] = '\0';

      return cli_helper::equals(tmpName, tmpKeyword) >= 0;
    }

    bool equals(String name) {
      if (!ReqArg_P::name) return false;

      int strLen = strlen_P(ReqArg_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, ReqArg_P::name);
      tmpKeyword[strLen] = '\0';

      return cli_helper::equals(name.c_str(), tmpKeyword) >= 0;
    }

    void setValue(String value) {
      if (value.length() > 0) {
        if (ReqArg_P::value) delete ReqArg_P::value;

        int strLen = value.length() + 1;
        ReqArg_P::value = new char[strLen];
        value.toCharArray(ReqArg_P::value, strLen);

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
    const char* name = NULL;
    char* value = NULL;
};

#endif
