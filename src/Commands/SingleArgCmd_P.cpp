#include "SingleArgCmd_P.h"

namespace arduino_cli {
    SingleArgCmd_P::SingleArgCmd_P(const char* name, void (*runFnct)(Cmd *)) {
        SingleArgCmd_P::runFnct = runFnct;

        SingleArgCmd_P::name = name;
        reset();
    }

    SingleArgCmd_P::~SingleArgCmd_P() {
        if (arg) delete arg;

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
        if (arg) delete arg;
        arg = NULL;
    }

    bool SingleArgCmd_P::parse(String argName, String argValue) {
        if (!arg) arg = new AnonymReqArg();
        arg->setValue(arg->getValue() + String(' ') + argName + String(' ') + argValue);

        return true;
    }

    int SingleArgCmd_P::argNum() {
        return arg ? 1 : 0;
    }

    Arg * SingleArgCmd_P::getArg(int i) {
        return i == 0 ? arg : NULL;
    }

    Arg * SingleArgCmd_P::getArg(const char* name) {
        return NULL;
    }

    Arg * SingleArgCmd_P::getArg(String name) {
        return NULL;
    }

    bool SingleArgCmd_P::isSet(int i) {
        if (i == 0) return arg;

        return false;
    }

    bool SingleArgCmd_P::isSet(const char* name) {
        return false;
    }

    bool SingleArgCmd_P::isSet(String name) {
        return false;
    }

    String SingleArgCmd_P::value(int i) {
        if ((i == 0) && arg) return arg->getValue();

        return String();
    }

    String SingleArgCmd_P::value(const char* name) {
        return String();
    }

    String SingleArgCmd_P::value(String name) {
        return String();
    }

    bool SingleArgCmd_P::isSet() {
        return arg;
    }
}