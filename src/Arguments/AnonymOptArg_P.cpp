#include "AnonymOptArg_P.h"

namespace arduino_cli {
    AnonymOptArg_P::AnonymOptArg_P(const char *defaultValue) {
        AnonymOptArg_P::defaultValue = defaultValue;
        reset();
    }

    AnonymOptArg_P::~AnonymOptArg_P() {
        if (value) delete value;

        if (next) delete next;
    }

    bool AnonymOptArg_P::equals(const char *name) {
        return strlen_P(name) == 0;
    }

    bool AnonymOptArg_P::equals(String name) {
        return name.length() == 0;
    }

    void AnonymOptArg_P::setValue(String value) {
        if (value.length() > 0) {
            if (AnonymOptArg_P::value) delete AnonymOptArg_P::value;

            int strLen = value.length() + 1;
            AnonymOptArg_P::value = new char[strLen];
            value.toCharArray(AnonymOptArg_P::value, strLen);

            set = true;
        }
    }

    void AnonymOptArg_P::reset() {
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

    String AnonymOptArg_P::getValue() {
        return value ? String(value) : String();
    }

    bool AnonymOptArg_P::isRequired() {
        return false;
    }
}
