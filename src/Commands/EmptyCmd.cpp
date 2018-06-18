#include "EmptyCmd.h"

namespace arduino_cli {
    EmptyCmd::EmptyCmd(const char* name, void (*runFnct)(Cmd*)) {
        EmptyCmd::runFnct = runFnct;

        if (name) {
            int strLen = strlen(name);
            EmptyCmd::name = new char[strLen + 1];
            strcpy(EmptyCmd::name, name);
            EmptyCmd::name[strLen] = '\0';
        }
        reset();
    }

    EmptyCmd::EmptyCmd(String name, void (*runFnct)(Cmd*)) {
        EmptyCmd::runFnct = runFnct;

        int strLen = name.length() + 1;
        EmptyCmd::name = new char[strLen];
        name.toCharArray(EmptyCmd::name, strLen);
        reset();
    }

    EmptyCmd::~EmptyCmd() {
        if (name) delete name;

        if (next) delete next;
    }

    String EmptyCmd::getName() {
        return String(name);
    }

    void EmptyCmd::reset() {}

    bool EmptyCmd::parse(String arg, String value) {
        return true;
    }

    int EmptyCmd::argNum() {
        return 0;
    }

    Arg* EmptyCmd::getArg(int i) {
        return NULL;
    }

    Arg* EmptyCmd::getArg(const char* name) {
        return NULL;
    }

    Arg* EmptyCmd::getArg(String name) {
        return NULL;
    }

    bool EmptyCmd::isSet(int i) {
        return false;
    }

    bool EmptyCmd::isSet(const char* name) {
        return false;
    }

    bool EmptyCmd::isSet(String name) {
        return false;
    }

    String EmptyCmd::getValue(int i) {
        return String();
    }

    String EmptyCmd::getValue(const char* name) {
        return String();
    }

    String EmptyCmd::getValue(String name) {
        return String();
    }

    bool EmptyCmd::isSet() {
        return true;
    }

    String EmptyCmd::toString() {
        return getName();
    }
}