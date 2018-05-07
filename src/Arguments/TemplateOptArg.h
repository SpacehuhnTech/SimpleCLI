#ifndef TemplateOptArg_h
#define TemplateOptArg_h

#include "Arg.h"

class TemplateOptArg: public Arg {
  public:
    TemplateOptArg(const char* _template) {
      if (_template) {
        int strLen = strlen_P(_template);
        TemplateOptArg::_template = new char[strLen + 1];
        strcpy_P(TemplateOptArg::_template, _template);
        TemplateOptArg::_template[strLen] = '\0';
      }

      reset();
    }

    TemplateOptArg(String _template) {
      int strLen = _template.length() + 1;
      TemplateOptArg::_template = new char[strLen];
      _template.toCharArray(TemplateOptArg::_template, strLen);
      reset();
    }

    ~TemplateOptArg() {
      if (_template) delete _template;
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
        index = cli_helper::equals(value.c_str(), _template);
        if (index >= 0) {
          if (TemplateOptArg::value) delete TemplateOptArg::value;

          int strLen = value.length() + 1;
          TemplateOptArg::value = new char[strLen];
          value.toCharArray(TemplateOptArg::value, strLen);

          set = true;
        }
      }
    }

    void reset() {
      if (value){
        delete value;
        value = NULL;
      }
      index = -1;
      Arg::reset();
    }

    String getValue() {
      return value ? String(value) : cli_helper::readTemplate(_template);
    }

    bool isRequired() {
      return false;
    }

    int getValueIndex(){
      return index >= 0 ? index : 0;
    }

  private:
    char* value = NULL;
    char* _template = NULL;
    int index = -1;
};

#endif
