#include "TemplateOptArg.h"

namespace arduino_cli {
    TemplateOptArg::TemplateOptArg(const char* _template) {
        if (_template) {
            int strLen = strlen(_template);
            TemplateOptArg::_template = new char[strLen + 1];
            strcpy(TemplateOptArg::_template, _template);
            TemplateOptArg::_template[strLen] = '\0';
        }

        reset();
    }

    TemplateOptArg::TemplateOptArg(String _template) {
        int strLen = _template.length() + 1;

        TemplateOptArg::_template = new char[strLen];
        _template.toCharArray(TemplateOptArg::_template, strLen);
        reset();
    }

    TemplateOptArg::~TemplateOptArg() {
        if (_template) delete _template;

        if (value) delete value;

        if (next) delete next;
    }

    bool TemplateOptArg::equals(const char* name) {
        return strlen(name) == 0;
    }

    bool TemplateOptArg::equals(String name) {
        return name.length() == 0;
    }

    void TemplateOptArg::setValue(String value) {
        if (value.length() > 0) {
            index = arduino_cli::equals(value.c_str(), _template);

            if (index >= 0) {
                if (TemplateOptArg::value) delete TemplateOptArg::value;

                int strLen = value.length() + 1;
                TemplateOptArg::value = new char[strLen];
                value.toCharArray(TemplateOptArg::value, strLen);

                set = true;
            }
        }
    }

    void TemplateOptArg::reset() {
        if (value) {
            delete value;
            value = NULL;
        }
        index = -1;
        Arg::reset();
    }

    String TemplateOptArg::getValue() {
        return value ? String(value) : readTemplate(_template);
    }

    bool TemplateOptArg::isRequired() {
        return false;
    }

    int TemplateOptArg::getValueIndex() {
        return index >= 0 ? index : 0;
    }
}