#include "AnonymOptArg.h"

namespace simplecli {
    AnonymOptArg::AnonymOptArg() {
        this->defaultValue = NULL;

        reset();
    }

    AnonymOptArg::AnonymOptArg(const char* defaultValue) {
        this->defaultValue = defaultValue;

        reset();
    }

    AnonymOptArg::~AnonymOptArg() {
        if (value) delete value;

        if (next) delete next;
    }

    bool AnonymOptArg::equals(const char* name) {
        return strlen_P(name) == 0;
    }

    bool AnonymOptArg::equals(String name) {
        return name.length() == 0;
    }

    void AnonymOptArg::setValue(String value) {
        if (value.length() > 0) {
            if (this->value) delete this->value;

            int strLen = value.length() + 1;
            this->value = new char[strLen];
            value.toCharArray(this->value, strLen);

            set = true;
        }
    }

    void AnonymOptArg::reset() {
        if (value) {
            delete value;
            value = NULL;
        }

        if (defaultValue) {
            int strLen = strlen_P(defaultValue);
            value = new char[strLen + 1];
            strcpy_P(value, defaultValue);
            value[strLen] = '\0';
        }

        Arg::reset();
    }

    String AnonymOptArg::getValue() {
        return value ? String(value) : String();
    }

    bool AnonymOptArg::isRequired() {
        return false;
    }

    String AnonymOptArg::getDefaultValue() {
        if (!defaultValue) return String();

        int  strLen = strlen_P(defaultValue);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, defaultValue);
        tmpName[strLen] = '\0';

        return String(tmpName);
    }

    String AnonymOptArg::toString() {
        return '[' + (defaultValue ? getDefaultValue() : "<value>") + ']';
    }
}
