#include "EmptyArg.h"

namespace simpleCLI {
    EmptyArg::EmptyArg(const char* name) {
        EmptyArg::name = name;

        reset();
    }

    EmptyArg::~EmptyArg() {
        if (next) delete next;
    }

    bool EmptyArg::equals(const char* name) {
        if (!name) return false;

        if (!EmptyArg::name) return false;

        if (name == EmptyArg::name) return true;

        int strLen;
        strLen = strlen_P(name);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, name);
        tmpName[strLen] = '\0';

        strLen = strlen_P(EmptyArg::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, EmptyArg::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(tmpName, tmpKeyword) >= 0;
    }

    bool EmptyArg::equals(String name) {
        if (!EmptyArg::name) return false;

        int  strLen = strlen_P(EmptyArg::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, EmptyArg::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(name.c_str(), tmpKeyword) >= 0;
    }

    void EmptyArg::setValue() {
        set = true;
    }

    void EmptyArg::setValue(String value) {
        setValue();
    }

    String EmptyArg::getName() {
        return readTemplate(name);
    }

    bool EmptyArg::isRequired() {
        return false;
    }

    String EmptyArg::toString() {
        return '[' + String('-') + getName() + ']';
    }
}