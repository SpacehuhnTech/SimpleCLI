#include "SingleArgCmd.h"

namespace simplecli {
    SingleArgCmd::SingleArgCmd(const char* name, CmdRunFunction) {
        this->runFnct = runFnct;
        this->name    = name;

        reset();
    }

    SingleArgCmd::~SingleArgCmd() {
        if (value) delete value;

        if (next) delete next;
    }

    String SingleArgCmd::getName() {
        return readTemplate(name);
    }

    void SingleArgCmd::reset() {
        if (value) delete value;
        value = NULL;
    }

    bool SingleArgCmd::parse(String argName, String argValue) {
        if (value) delete value;

        int strLen = argValue.length() + 1;
        value = new char[strLen];
        argValue.toCharArray(value, strLen);

        return true;
    }

    int SingleArgCmd::argNum() {
        return value ? 1 : -1;
    }

    Arg* SingleArgCmd::getArg(int i) {
        return NULL;
    }

    Arg* SingleArgCmd::getArg(const char* name) {
        return NULL;
    }

    Arg* SingleArgCmd::getArg(String name) {
        return NULL;
    }

    bool SingleArgCmd::isSet(int i) {
        return i == 0 ? value : false;
    }

    bool SingleArgCmd::isSet(const char* name) {
        return false;
    }

    bool SingleArgCmd::isSet(String name) {
        return false;
    }

    String SingleArgCmd::getValue(int i) {
        return i == 0 ? String(value) : String();
    }

    String SingleArgCmd::getValue(const char* name) {
        return String();
    }

    String SingleArgCmd::getValue(String name) {
        return String();
    }

    bool SingleArgCmd::isSet() {
        return value;
    }

    String SingleArgCmd::toString() {
        return getName() + " [...]";
    }
}