#include "SingleArgCmd_P.h"

namespace arduino_cli {
    SingleArgCmd_P::SingleArgCmd_P(const char* name, void (*runFnct)(Cmd*)) {
        SingleArgCmd_P::runFnct = runFnct;

        SingleArgCmd_P::name = name;
        reset();
    }

    SingleArgCmd_P::~SingleArgCmd_P() {
        if (value) delete value;

        if (next) delete next;
    }

    String SingleArgCmd_P::getName() {
        int  strLen = strlen_P(name);
        char tmpName[strLen + 1];

        strcpy_P(tmpName, name);
        tmpName[strLen] = '\0';
        return String(tmpName);
    }

    void SingleArgCmd_P::reset() {
        if (value) delete value;
        value = NULL;
    }

    bool SingleArgCmd_P::parse(String argName, String argValue) {
        if (value) delete value;

        int strLen = argValue.length() + 1;
        value = new char[strLen];
        argValue.toCharArray(value, strLen);

        return true;
    }

    int SingleArgCmd_P::argNum() {
        return value ? 1 : -1;
    }

    Arg* SingleArgCmd_P::getArg(int i) {
        return NULL;
    }

    Arg* SingleArgCmd_P::getArg(const char* name) {
        return NULL;
    }

    Arg* SingleArgCmd_P::getArg(String name) {
        return NULL;
    }

    bool SingleArgCmd_P::isSet(int i) {
        return i == 0 ? value : false;
    }

    bool SingleArgCmd_P::isSet(const char* name) {
        return false;
    }

    bool SingleArgCmd_P::isSet(String name) {
        return false;
    }

    String SingleArgCmd_P::getValue(int i) {
        return i == 0 ? String(value) : String();
    }

    String SingleArgCmd_P::getValue(const char* name) {
        return String();
    }

    String SingleArgCmd_P::getValue(String name) {
        return String();
    }

    bool SingleArgCmd_P::isSet() {
        return value;
    }
}