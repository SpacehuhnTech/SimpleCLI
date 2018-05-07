#ifndef TemplateOptArg_P_h
#define TemplateOptArg_P_h

#include "Arg.h"

class TemplateOptArg_P: public Arg {
  public:
    TemplateOptArg_P(const char* _template) {
      TemplateOptArg_P::_template = _template;
      reset();
    }

    ~TemplateOptArg_P() {
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      return strlen_P(name) == 0;
    }

    bool equals(String name) {
      return name.length() == 0;
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

        index = cli_helper::equals(value.c_str(), tmpTemplate);
        if (index >= 0) {
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
    const char* _template = NULL;
    int index = -1;
};

#endif
