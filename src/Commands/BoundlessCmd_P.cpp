#include "BoundlessCmd_P.h"

namespace arduino_cli {
    BoundlessCmd_P::BoundlessCmd_P(const char *name, void (*runFnct)(Cmd *)) {
        BoundlessCmd_P::runFnct = runFnct;

        BoundlessCmd_P::name = name;
        reset();
    }

    BoundlessCmd_P::~BoundlessCmd_P() {
        if (firstArg) delete firstArg;

        if (next) delete next;
    }

    String BoundlessCmd_P::getName() {
        int  strLen = strlen_P(name);
        char tmpName[strLen + 1];

        strcpy_P(tmpName, name);
        tmpName[strLen] = '\0';
        return String(tmpName);
    }

    void BoundlessCmd_P::reset() {
        if (firstArg) delete firstArg;
        firstArg = NULL;
        lastArg  = NULL;
        args     = 0;
    }

    bool BoundlessCmd_P::parse(String arg, String value) {
        bool success = false;

        if (arg.length() > 0) {
            Arg *newArg = new AnonymReqArg();
            newArg->setValue(arg);

            if (lastArg) lastArg->next = newArg;

            if (!firstArg) firstArg = newArg;
            lastArg = newArg;
            args++;

            success = true;
        }

        if (value.length() > 0) {
            Arg *newArg = new AnonymReqArg();
            newArg->setValue(value);

            if (lastArg) lastArg->next = newArg;

            if (!firstArg) firstArg = newArg;
            lastArg = newArg;
            args++;

            success = true;
        }

        return success;
    }

    int BoundlessCmd_P::argNum() {
        return args;
    }

    Arg * BoundlessCmd_P::getArg(int i) {
        int  j = 0;
        Arg *h = firstArg;

        while (j < i && h) {
            j++;
            h = h->next;
        }
        return h;
    }

    Arg * BoundlessCmd_P::getArg(const char *name) {
        Arg *h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    Arg * BoundlessCmd_P::getArg(String name) {
        Arg *h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    bool BoundlessCmd_P::isSet(int i) {
        Arg *h = getArg(i);

        return h ? h->isSet() : false;
    }

    bool BoundlessCmd_P::isSet(const char *name) {
        Arg *h = getArg(name);

        return h ? h->isSet() : false;
    }

    bool BoundlessCmd_P::isSet(String name) {
        Arg *h = getArg(name);

        return h ? h->isSet() : false;
    }

    String BoundlessCmd_P::value(int i) {
        Arg *h = getArg(i);

        return h ? h->getValue() : String();
    }

    String BoundlessCmd_P::value(const char *name) {
        Arg *h = getArg(name);

        return h ? h->getValue() : String();
    }

    String BoundlessCmd_P::value(String name) {
        Arg *h = getArg(name);

        return h ? h->getValue() : String();
    }

    bool BoundlessCmd_P::isSet() {
        return true;
    }
}