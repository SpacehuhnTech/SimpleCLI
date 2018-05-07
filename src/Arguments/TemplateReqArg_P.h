#ifndef TemplateReqArg_P_h
#define TemplateReqArg_P_h

#include "Arg.h"

class TemplateReqArg_P: public Arg {
  public:
    TemplateReqArg_P(const char* _template) {
      TemplateReqArg_P::_template = _template;
      reset();
    }

    ~TemplateReqArg_P() {
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
          if (TemplateReqArg_P::value) delete TemplateReqArg_P::value;

          int strLen = value.length() + 1;
          TemplateReqArg_P::value = new char[strLen];
          value.toCharArray(TemplateReqArg_P::value, strLen);

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
      return value ? String(value) : String();
    }

    bool isRequired() {
      return true;
    }

    int getValueIndex(){
      return index;
    }

  private:
    char* value = NULL;
    const char* _template = NULL;
    int index = -1;
};

#endif
