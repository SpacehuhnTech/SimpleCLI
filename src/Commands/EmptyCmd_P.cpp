#include "EmptyCmd_P.h"

namespace simpleCLI {
    EmptyCmd_P::EmptyCmd_P(const char* name, void (*runFnct)(Cmd*)) {
        EmptyCmd_P::runFnct = runFnct;

        EmptyCmd_P::name = name;
        reset();
    }

    EmptyCmd_P::~EmptyCmd_P() {
        if (next) delete next;
    }

    String EmptyCmd_P::getName() {
        return readTemplate(name);
    }

    void EmptyCmd_P::reset() {}

    bool EmptyCmd_P::parse(String arg, String value) {
        return true;
    }

    int EmptyCmd_P::argNum() {
        return 0;
    }

    Arg* EmptyCmd_P::getArg(int i) {
        return NULL;
    }

    Arg* EmptyCmd_P::getArg(const char* name) {
        return NULL;
    }

    Arg* EmptyCmd_P::getArg(String name) {
        return NULL;
    }

    bool EmptyCmd_P::isSet(int i) {
        return false;
    }

    bool EmptyCmd_P::isSet(const char* name) {
        return false;
    }

    bool EmptyCmd_P::isSet(String name) {
        return false;
    }

    String EmptyCmd_P::getValue(int i) {
        return String();
    }

    String EmptyCmd_P::getValue(const char* name) {
        return String();
    }

    String EmptyCmd_P::getValue(String name) {
        return String();
    }

    bool EmptyCmd_P::isSet() {
        return true;
    }

    String EmptyCmd_P::toString() {
        return getName();
    }
}