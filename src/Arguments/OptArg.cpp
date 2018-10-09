#include "OptArg.h"

namespace simpleCLI {
    OptArg::OptArg(const char* name) {
        OptArg::name         = name;
        OptArg::defaultValue = NULL;

        reset();
    }

    OptArg::OptArg(const char* name, const char* defaultValue) {
        OptArg::name         = name;
        OptArg::defaultValue = defaultValue;

        reset();
    }

    OptArg::~OptArg() {
        if (value) delete value;

        if (next) delete next;
    }

    bool OptArg::equals(const char* name) {
        if (!name) return false;

        if (!OptArg::name) return false;

        if (name == OptArg::name) return true;

        int strLen;
        strLen = strlen_P(name);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, name);
        tmpName[strLen] = '\0';

        strLen = strlen_P(OptArg::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, OptArg::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(tmpName, tmpKeyword) >= 0;
    }

    bool OptArg::equals(String name) {
        if (!OptArg::name) return false;

        int  strLen = strlen_P(OptArg::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, OptArg::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(name.c_str(), tmpKeyword) >= 0;
    }

    void OptArg::setValue(String value) {
        if (value.length() > 0) {
            if (OptArg::value) delete OptArg::value;

            int strLen = value.length() + 1;
            OptArg::value = new char[strLen];
            value.toCharArray(OptArg::value, strLen);

            set = true;
        }
    }

    void OptArg::reset() {
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

    String OptArg::getName() {
        return readTemplate(name);
    }

    String OptArg::getValue() {
        return value ? String(value) : String();
    }

    bool OptArg::isRequired() {
        return false;
    }

    String OptArg::getDefaultValue() {
        if (!defaultValue) return String();

        int  strLen = strlen_P(defaultValue);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, defaultValue);
        tmpName[strLen] = '\0';

        return String(tmpName);
    }

    String OptArg::toString() {
        return '[' + String('-') + getName() + ' ' + (defaultValue ? getDefaultValue() : "<value>") + ']';
    }
}