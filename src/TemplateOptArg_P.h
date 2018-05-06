#ifndef TemplateOptArg_P_h
#define TemplateOptArg_P_h

#include "Arg.h"

class TemplateOptArg_P: public Arg {
  public:
    TemplateOptArg_P(const char* _template, const char* defaultValue) {
      TemplateOptArg_P::_template = _template;
      TemplateOptArg_P::defaultValue = defaultValue;
      reset();
    }

    ~TemplateOptArg_P() {
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      return false;
    }

    bool equals(String name) {
      return false;
    }

    void setValue(String value) {
      if (value.length() > 0) {
        char* tmpTemplate = NULL;

        if (_template) {
          int strLen = strlen_P(_template);;
          tmpTemplate = new char[strLen + 1];
          strcpy_P(tmpTemplate, _template);
          tmpTemplate[strLen] = '\0';
        }

        if (cli_helper::equals(value.c_str(), tmpTemplate)) {
          if (TemplateOptArg_P::value) delete TemplateOptArg_P::value;

          int strLen = value.length() + 1;
          TemplateOptArg_P::value = new char[strLen];
          value.toCharArray(TemplateOptArg_P::value, strLen);

          set = true;
        }

        delete tmpTemplate;
      }
    }

    void reset() {
      if (value) delete value;

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
    const char* _template = NULL;
};

#endif

