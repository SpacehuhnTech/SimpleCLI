#include "BoundlessCmd.h"

namespace simplecli {
    BoundlessCmd::BoundlessCmd(const char* name, CmdRunFunction) {
        this->runFnct = runFnct;
        this->name    = name;

        reset();
    }

    BoundlessCmd::~BoundlessCmd() {
        if (firstArg) delete firstArg;

        if (next) delete next;
    }

    String BoundlessCmd::getName() {
        return readTemplate(name);
    }

    void BoundlessCmd::reset() {
        if (firstArg) delete firstArg;
        firstArg = NULL;
        lastArg  = NULL;
        args     = 0;
    }

    bool BoundlessCmd::parse(String arg, String value) {
        bool success = false;

        if (arg.length() > 0) {
            Arg* newArg = new AnonymReqArg();
            newArg->setValue(arg);

            if (lastArg) lastArg->next = newArg;

            if (!firstArg) firstArg = newArg;
            lastArg = newArg;
            args++;

            success = true;
        }

        if (value.length() > 0) {
            Arg* newArg = new AnonymReqArg();
            newArg->setValue(value);

            if (lastArg) lastArg->next = newArg;

            if (!firstArg) firstArg = newArg;
            lastArg = newArg;
            args++;

            success = true;
        }

        return success;
    }

    int BoundlessCmd::argNum() {
        return args;
    }

    Arg* BoundlessCmd::getArg(int i) {
        int  j = 0;
        Arg* h = firstArg;

        while (j < i && h) {
            j++;
            h = h->next;
        }
        return h;
    }

    Arg* BoundlessCmd::getArg(const char* name) {
        Arg* h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    Arg* BoundlessCmd::getArg(String name) {
        Arg* h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    bool BoundlessCmd::isSet(int i) {
        Arg* h = getArg(i);

        return h ? h->isSet() : false;
    }

    bool BoundlessCmd::isSet(const char* name) {
        Arg* h = getArg(name);

        return h ? h->isSet() : false;
    }

    bool BoundlessCmd::isSet(String name) {
        Arg* h = getArg(name);

        return h ? h->isSet() : false;
    }

    String BoundlessCmd::getValue(int i) {
        Arg* h = getArg(i);

        return h ? h->getValue() : String();
    }

    String BoundlessCmd::getValue(const char* name) {
        Arg* h = getArg(name);

        return h ? h->getValue() : String();
    }

    String BoundlessCmd::getValue(String name) {
        Arg* h = getArg(name);

        return h ? h->getValue() : String();
    }

    bool BoundlessCmd::isSet() {
        return true;
    }

    String BoundlessCmd::toString() {
        return getName() + " [...]";
    }
}