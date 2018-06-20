#include "OptArg_P.h"

namespace simpleCLI {
    OptArg_P::OptArg_P(const char* name, const char* defaultValue) {
        OptArg_P::name         = name;
        OptArg_P::defaultValue = defaultValue;

        reset();
    }

    OptArg_P::~OptArg_P() {
        if (value) delete value;

        if (next) delete next;
    }

    bool OptArg_P::equals(const char* name) {
        if (!name) return false;

        if (!OptArg_P::name) return false;

        if (name == OptArg_P::name) return true;

        int strLen;
        strLen = strlen_P(name);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, name);
        tmpName[strLen] = '\0';

        strLen = strlen_P(OptArg_P::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, OptArg_P::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(tmpName, tmpKeyword) >= 0;
    }

    bool OptArg_P::equals(String name) {
        if (!OptArg_P::name) return false;

        int  strLen = strlen_P(OptArg_P::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, OptArg_P::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(name.c_str(), tmpKeyword) >= 0;
    }

    void OptArg_P::setValue(String value) {
        if (value.length() > 0) {
            if (OptArg_P::value) delete OptArg_P::value;

            int strLen = value.length() + 1;
            OptArg_P::value = new char[strLen];
            value.toCharArray(OptArg_P::value, strLen);

            set = true;
        }
    }

    void OptArg_P::reset() {
        if (value) {
            delete value;
            value = NULL;
        }

        int strLen = strlen_P(defaultValue);
        value = new char[strLen + 1];
        strcpy_P(value, defaultValue);
        value[strLen] = '\0';

        Arg::reset();
    }

    String OptArg_P::getName() {
        return readTemplate(name);
    }

    String OptArg_P::getValue() {
        return value ? String(value) : String();
    }

    bool OptArg_P::isRequired() {
        return false;
    }

    String OptArg_P::getDefaultValue() {
        if (!defaultValue) return String();

        int  strLen = strlen_P(defaultValue);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, defaultValue);
        tmpName[strLen] = '\0';

        return String(tmpName);
    }

    String OptArg_P::toString() {
        return '[' + String('-') + getName() + ' ' + getDefaultValue() + ']';
    }
}
