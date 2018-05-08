#include "BoundlessCmd.h"

namespace arduino_cli {
    BoundlessCmd::BoundlessCmd(const char *name, void (*runFnct)(Cmd *)) {
        BoundlessCmd::runFnct = runFnct;

        if (name) {
            int strLen = strlen(name);
            BoundlessCmd::name = new char[strLen + 1];
            strcpy(BoundlessCmd::name, name);
            BoundlessCmd::name[strLen] = '\0';
        }
        reset();
    }

    BoundlessCmd::BoundlessCmd(String name, void (*runFnct)(Cmd *)) {
        BoundlessCmd::runFnct = runFnct;

        int strLen = name.length() + 1;
        BoundlessCmd::name = new char[strLen];
        name.toCharArray(BoundlessCmd::name, strLen);
        reset();
    }

    BoundlessCmd::~BoundlessCmd() {
        if (name) delete name;

        if (firstArg) delete firstArg;

        if (next) delete next;
    }

    String BoundlessCmd::getName() {
        return String(name);
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

    int BoundlessCmd::argNum() {
        return args;
    }

    Arg * BoundlessCmd::getArg(int i) {
        int  j = 0;
        Arg *h = firstArg;

        while (j < i && h) {
            j++;
            h = h->next;
        }
        return h;
    }

    Arg * BoundlessCmd::getArg(const char *name) {
        Arg *h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    Arg * BoundlessCmd::getArg(String name) {
        Arg *h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    bool BoundlessCmd::isSet(int i) {
        Arg *h = getArg(i);

        return h ? h->isSet() : false;
    }

    bool BoundlessCmd::isSet(const char *name) {
        Arg *h = getArg(name);

        return h ? h->isSet() : false;
    }

    bool BoundlessCmd::isSet(String name) {
        Arg *h = getArg(name);

        return h ? h->isSet() : false;
    }

    String BoundlessCmd::value(int i) {
        Arg *h = getArg(i);

        return h ? h->getValue() : String();
    }

    String BoundlessCmd::value(const char *name) {
        Arg *h = getArg(name);

        return h ? h->getValue() : String();
    }

    String BoundlessCmd::value(String name) {
        Arg *h = getArg(name);

        return h ? h->getValue() : String();
    }

    bool BoundlessCmd::isSet() {
        return true;
    }
}