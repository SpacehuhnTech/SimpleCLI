#include "EmptyArg.h"

namespace arduino_cli {
    EmptyArg::EmptyArg(const char* name) {
        if (name) {
            int strLen = strlen(name);
            EmptyArg::name = new char[strLen + 1];
            strcpy(EmptyArg::name, name);
            EmptyArg::name[strLen] = '\0';
        }

        reset();
    }

    EmptyArg::EmptyArg(String name) {
        int strLen = name.length() + 1;

        EmptyArg::name = new char[strLen];
        name.toCharArray(EmptyArg::name, strLen);
        reset();
    }

    EmptyArg::~EmptyArg() {
        if (name) delete name;

        if (next) delete next;
    }

    bool EmptyArg::equals(const char* name) {
        if (!name) return false;

        if (!EmptyArg::name) return false;

        if (name == EmptyArg::name) return true;

        return arduino_cli::equals(name, EmptyArg::name) >= 0;
    }

    bool EmptyArg::equals(String name) {
        return arduino_cli::equals(name.c_str(), EmptyArg::name) >= 0;
    }

    void EmptyArg::setValue() {
        set = true;
    }

    void EmptyArg::setValue(String value) {
        setValue();
    }

    String EmptyArg::getName() {
        return name ? String(name) : String();
    }

    bool EmptyArg::isRequired() {
        return false;
    }

    String EmptyArg::toString() {
        return '[' + String('-') + getName() + ']';
    }
}