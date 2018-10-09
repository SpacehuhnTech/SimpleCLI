#include "EmptyCmd.h"

namespace simplecli {
    EmptyCmd::EmptyCmd(const char* name, CmdRunFunction) {
        this->runFnct = runFnct;
        this->name    = name;

        reset();
    }

    EmptyCmd::~EmptyCmd() {
        if (next) delete next;
    }

    String EmptyCmd::getName() {
        return readTemplate(name);
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