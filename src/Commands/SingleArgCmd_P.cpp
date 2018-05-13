#include "SingleArgCmd_P.h"

namespace arduino_cli {
    SingleArgCmd_P::SingleArgCmd_P(const char* name, void (*runFnct)(Cmd*)) {
        SingleArgCmd_P::runFnct = runFnct;

        SingleArgCmd_P::name = name;
        reset();
    }

    SingleArgCmd_P::~SingleArgCmd_P() {
        if (val) delete val;

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
        if (val) delete val;
        val = NULL;
    }

    bool SingleArgCmd_P::parse(String argName, String argValue) {
        if (val) delete val;

        int strLen = argValue.length() + 1;
        val = new char[strLen];
        argValue.toCharArray(val, strLen);

        return true;
    }

    int SingleArgCmd_P::argNum() {
        return val ? 1 : -1;
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
        return i == 0 ? val : false;
    }

    bool SingleArgCmd_P::isSet(const char* name) {
        return false;
    }

    bool SingleArgCmd_P::isSet(String name) {
        return false;
    }

    String SingleArgCmd_P::value(int i) {
        return i == 0 ? String(val) : String();
    }

    String SingleArgCmd_P::value(const char* name) {
        return String();
    }

    String SingleArgCmd_P::value(String name) {
        return String();
    }

    bool SingleArgCmd_P::isSet() {
        return val;
    }
}