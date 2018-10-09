#include "TemplateReqArg.h"

namespace simplecli {
    TemplateReqArg::TemplateReqArg(const char* _template) {
        this->_template = _template;

        reset();
    }

    TemplateReqArg::~TemplateReqArg() {
        if (value) delete value;

        if (next) delete next;
    }

    bool TemplateReqArg::equals(const char* name) {
        return strlen_P(name) == 0;
    }

    bool TemplateReqArg::equals(String name) {
        return name.length() == 0;
    }

    void TemplateReqArg::setValue(String value) {
        if (value.length() > 0) {
            char* tmpTemplate = NULL;

            if (_template) {
                int strLen = strlen_P(_template);
                tmpTemplate = new char[strLen + 1];
                strcpy_P(tmpTemplate, _template);
                tmpTemplate[strLen] = '\0';
            }

            index = simplecli::equals(value.c_str(), tmpTemplate);

            if (index >= 0) {
                if (this->value) delete this->value;

                int strLen = value.length() + 1;
                this->value = new char[strLen];
                value.toCharArray(this->value, strLen);

                set = true;
            }

            delete tmpTemplate;
        }
    }

    void TemplateReqArg::reset() {
        if (value) {
            delete value;
            value = NULL;
        }
        index = -1;
        Arg::reset();
    }

    String TemplateReqArg::getValue() {
        return value ? String(value) : String();
    }

    bool TemplateReqArg::isRequired() {
        return true;
    }

    int TemplateReqArg::getValueIndex() {
        return index;
    }

    String TemplateReqArg::toString() {
        return '<' + readTemplate(_template) + '>';
    }
}
