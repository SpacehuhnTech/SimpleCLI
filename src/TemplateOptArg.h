#ifndef TemplateOptArg_h
#define TemplateOptArg_h

#include "Arg.h"

class TemplateOptArg: public Arg {
  public:
    TemplateOptArg(const char* _template, const char* defaultValue) {
      if (_template) {
        int strLen = strlen_P(_template);
        TemplateOptArg::_template = new char[strLen + 1];
        strcpy_P(TemplateOptArg::_template, _template);
        TemplateOptArg::_template[strLen] = '\0';
      }

      if (defaultValue) {
        int strLen = strlen_P(defaultValue);
        TemplateOptArg::defaultValue = new char[strLen + 1];
        strcpy_P(TemplateOptArg::defaultValue, defaultValue);
        TemplateOptArg::defaultValue[strLen] = '\0';
      }
      reset();
    }

    TemplateOptArg(String _template, String defaultValue) {
      int strLen = _template.length() + 1;
      TemplateOptArg::_template = new char[strLen];
      _template.toCharArray(TemplateOptArg::_template, strLen);

      strLen = defaultValue.length() + 1;
      TemplateOptArg::defaultValue = new char[strLen];
      _template.toCharArray(TemplateOptArg::defaultValue, strLen);

      reset();
    }

    ~TemplateOptArg() {
      if (_template) delete _template;
      if (defaultValue) delete defaultValue;
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
        if (cli_helper::equals(value.c_str(), _template)) {
          if (TemplateOptArg::value) delete TemplateOptArg::value;

          int strLen = value.length() + 1;
          TemplateOptArg::value = new char[strLen];
          value.toCharArray(TemplateOptArg::value, strLen);

          set = true;
        }
      }
    }

    void reset() {
      if (value) delete value;

      int strLen = strlen(defaultValue);
      value = new char[strLen + 1];
      strcpy(value, defaultValue);
      value[strLen] = '\0';

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
    char* _template = NULL;
};

#endif

