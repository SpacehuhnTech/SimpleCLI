#include "OptArg.h"

namespace arduino_cli {
    OptArg::OptArg(const char *name, const char *defaultValue) {
        if (name) {
            int strLen = strlen(name);
            OptArg::name = new char[strLen + 1];
            strcpy(OptArg::name, name);
            OptArg::name[strLen] = '\0';
        }

        if (defaultValue) {
            int strLen = strlen(defaultValue);
            OptArg::defaultValue = new char[strLen + 1];
            strcpy(OptArg::defaultValue, defaultValue);
            OptArg::defaultValue[strLen] = '\0';
        }

        reset();
    }

    OptArg::OptArg(String name, String defaultValue) {
        int strLen;

        strLen       = name.length() + 1;
        OptArg::name = new char[strLen];
        name.toCharArray(OptArg::name, strLen);

        strLen               = defaultValue.length() + 1;
        OptArg::defaultValue = new char[strLen];
        defaultValue.toCharArray(OptArg::defaultValue, strLen);

        reset();
    }

    OptArg::~OptArg() {
        if (name) delete name;

        if (defaultValue) delete defaultValue;

        if (value) delete value;

        if (next) delete next;
    }

    bool OptArg::equals(const char *name) {
        if (!name) return false;

        if (!OptArg::name) return false;

        if (name == OptArg::name) return true;

        return arduino_cli::equals(name, OptArg::name) >= 0;
    }

    bool OptArg::equals(String name) {
        return arduino_cli::equals(name.c_str(), OptArg::name) >= 0;
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
            int strLen = strlen(defaultValue);
            value = new char[strLen + 1];
            strcpy(value, defaultValue);
            value[strLen] = '\0';
        }

        Arg::reset();
    }

    String OptArg::getName() {
        return name ? String(name) : String();
    }

    String OptArg::getValue() {
        return value ? String(value) : String();
    }

    bool OptArg::isRequired() {
        return false;
    }
}