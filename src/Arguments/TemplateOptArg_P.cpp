#include "TemplateOptArg_P.h"

namespace simpleCLI {
    TemplateOptArg_P::TemplateOptArg_P(const char* _template) {
        TemplateOptArg_P::_template = _template;
        reset();
    }

    TemplateOptArg_P::~TemplateOptArg_P() {
        if (value) delete value;

        if (next) delete next;
    }

    bool TemplateOptArg_P::equals(const char* name) {
        return strlen_P(name) == 0;
    }

    bool TemplateOptArg_P::equals(String name) {
        return name.length() == 0;
    }

    void TemplateOptArg_P::setValue(String value) {
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
                if (TemplateOptArg_P::value) delete TemplateOptArg_P::value;

                int strLen = value.length() + 1;
                TemplateOptArg_P::value = new char[strLen];
                value.toCharArray(TemplateOptArg_P::value, strLen);

                set = true;
            }

            delete tmpTemplate;
        }
    }

    void TemplateOptArg_P::reset() {
        if (value) {
            delete value;
            value = NULL;
        }
        index = -1;
        Arg::reset();
    }

    String TemplateOptArg_P::getValue() {
        return value ? String(value) : readTemplate(_template);
    }

    bool TemplateOptArg_P::isRequired() {
        return false;
    }

    int TemplateOptArg_P::getValueIndex() {
        return index >= 0 ? index : 0;
    }

    String TemplateOptArg_P::toString() {
        return "[<" + readTemplate(_template) + ">]";
    }
}