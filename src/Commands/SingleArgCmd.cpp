#include "SingleArgCmd.h"

namespace arduino_cli {
    SingleArgCmd::SingleArgCmd(const char* name, void (*runFnct)(Cmd *)) {
        SingleArgCmd::runFnct = runFnct;

        if (name) {
            int strLen = strlen(name);
            SingleArgCmd::name = new char[strLen + 1];
            strcpy(SingleArgCmd::name, name);
            SingleArgCmd::name[strLen] = '\0';
        }
        reset();
    }

    SingleArgCmd::SingleArgCmd(String name, void (*runFnct)(Cmd *)) {
        SingleArgCmd::runFnct = runFnct;

        int strLen = name.length() + 1;
        SingleArgCmd::name = new char[strLen];
        name.toCharArray(SingleArgCmd::name, strLen);
        reset();
    }

    SingleArgCmd::~SingleArgCmd() {
        if (name) delete name;

        if (arg) delete arg;

        if (next) delete next;
    }

    String SingleArgCmd::getName() {
        return String(name);
    }

    void SingleArgCmd::reset() {
        if (arg) delete arg;
        arg = NULL;
    }

    bool SingleArgCmd::parse(String argName, String argValue) {
        if (!arg) arg = new AnonymReqArg();
        arg->setValue(arg->getValue() + String(' ') + argName + String(' ') + argValue);

        return true;
    }

    int SingleArgCmd::argNum() {
        return arg ? 1 : 0;
    }

    Arg * SingleArgCmd::getArg(int i) {
        return i == 0 ? arg : NULL;
    }

    Arg * SingleArgCmd::getArg(const char* name) {
        return NULL;
    }

    Arg * SingleArgCmd::getArg(String name) {
        return NULL;
    }

    bool SingleArgCmd::isSet(int i) {
        if (i == 0) return arg;

        return false;
    }

    bool SingleArgCmd::isSet(const char* name) {
        return false;
    }

    bool SingleArgCmd::isSet(String name) {
        return false;
    }

    String SingleArgCmd::value(int i) {
        if ((i == 0) && arg) return arg->getValue();

        return String();
    }

    String SingleArgCmd::value(const char* name) {
        return String();
    }

    String SingleArgCmd::value(String name) {
        return String();
    }

    bool SingleArgCmd::isSet() {
        return arg;
    }
}