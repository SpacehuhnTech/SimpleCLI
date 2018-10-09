#include "TemplateOptArg.h"

namespace simplecli {
    TemplateOptArg::TemplateOptArg(const char* _template) {
        this->_template = _template;

        reset();
    }

    TemplateOptArg::~TemplateOptArg() {
        if (value) delete value;

        if (next) delete next;
    }

    bool TemplateOptArg::equals(const char* name) {
        return strlen_P(name) == 0;
    }

    bool TemplateOptArg::equals(String name) {
        return name.length() == 0;
    }

    void TemplateOptArg::setValue(String value) {
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

    String TemplateOptArg::toString() {
        return "[<" + readTemplate(_template) + ">]";
    }
}
