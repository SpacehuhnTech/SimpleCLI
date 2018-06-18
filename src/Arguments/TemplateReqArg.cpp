#include "TemplateReqArg.h"

namespace arduino_cli {
    TemplateReqArg::TemplateReqArg(const char* _template) {
        if (_template) {
            int strLen = strlen(_template);
            TemplateReqArg::_template = new char[strLen + 1];
            strcpy(TemplateReqArg::_template, _template);
            TemplateReqArg::_template[strLen] = '\0';
        }
        reset();
    }

    TemplateReqArg::TemplateReqArg(String _template) {
        int strLen = _template.length() + 1;

        TemplateReqArg::_template = new char[strLen];
        _template.toCharArray(TemplateReqArg::_template, strLen);

        reset();
    }

    TemplateReqArg::~TemplateReqArg() {
        if (_template) delete _template;

        if (value) delete value;

        if (next) delete next;
    }

    bool TemplateReqArg::equals(const char* name) {
        return strlen(name) == 0;
    }

    bool TemplateReqArg::equals(String name) {
        return name.length() == 0;
    }

    void TemplateReqArg::setValue(String value) {
        if (value.length() > 0) {
            index = arduino_cli::equals(value.c_str(), _template);

            if (index >= 0) {
                if (TemplateReqArg::value) delete TemplateReqArg::value;

                int strLen = value.length() + 1;
                TemplateReqArg::value = new char[strLen];
                value.toCharArray(TemplateReqArg::value, strLen);

                set = true;
            }
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
        return readTemplate(_template);
    }
}