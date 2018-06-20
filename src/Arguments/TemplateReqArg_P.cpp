#include "TemplateReqArg_P.h"

namespace simpleCLI {
    TemplateReqArg_P::TemplateReqArg_P(const char* _template) {
        TemplateReqArg_P::_template = _template;
        reset();
    }

    TemplateReqArg_P::~TemplateReqArg_P() {
        if (value) delete value;

        if (next) delete next;
    }

    bool TemplateReqArg_P::equals(const char* name) {
        return strlen_P(name) == 0;
    }

    bool TemplateReqArg_P::equals(String name) {
        return name.length() == 0;
    }

    void TemplateReqArg_P::setValue(String value) {
        if (value.length() > 0) {
            char* tmpTemplate = NULL;

            if (_template) {
                int strLen = strlen_P(_template);
                tmpTemplate = new char[strLen + 1];
                strcpy_P(tmpTemplate, _template);
                tmpTemplate[strLen] = '\0';
            }

            index = simpleCLI::equals(value.c_str(), tmpTemplate);

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

    void TemplateReqArg_P::reset() {
        if (value) {
            delete value;
            value = NULL;
        }
        index = -1;
        Arg::reset();
    }

    String TemplateReqArg_P::getValue() {
        return value ? String(value) : String();
    }

    bool TemplateReqArg_P::isRequired() {
        return true;
    }

    int TemplateReqArg_P::getValueIndex() {
        return index;
    }

    String TemplateReqArg_P::toString() {
        return readTemplate(_template);
    }
}