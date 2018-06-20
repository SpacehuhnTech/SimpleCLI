#include "EmptyArg_P.h"

namespace simpleCLI {
    EmptyArg_P::EmptyArg_P(const char* name) {
        EmptyArg_P::name = name;

        reset();
    }

    EmptyArg_P::~EmptyArg_P() {
        if (next) delete next;
    }

    bool EmptyArg_P::equals(const char* name) {
        if (!name) return false;

        if (!EmptyArg_P::name) return false;

        if (name == EmptyArg_P::name) return true;

        int strLen;
        strLen = strlen_P(name);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, name);
        tmpName[strLen] = '\0';

        strLen = strlen_P(EmptyArg_P::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, EmptyArg_P::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(tmpName, tmpKeyword) >= 0;
    }

    bool EmptyArg_P::equals(String name) {
        if (!EmptyArg_P::name) return false;

        int  strLen = strlen_P(EmptyArg_P::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, EmptyArg_P::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(name.c_str(), tmpKeyword) >= 0;
    }

    void EmptyArg_P::setValue() {
        set = true;
    }

    void EmptyArg_P::setValue(String value) {
        setValue();
    }

    String EmptyArg_P::getName() {
        return readTemplate(name);
    }

    bool EmptyArg_P::isRequired() {
        return false;
    }

    String EmptyArg_P::toString() {
        return '[' + String('-') + getName() + ']';
    }
}