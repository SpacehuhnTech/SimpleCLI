#include "Command_P.h"

namespace simpleCLI {
    Command_P::Command_P(const char* name, void(*runFnct)(Cmd*)) {
        Command_P::runFnct = runFnct;

        Command_P::name = name;

        reset();
    }

    Command_P::~Command_P() {
        if (firstArg) delete firstArg;

        if (next) delete next;
    }

    String Command_P::getName() {
        return readTemplate(name);
    }

    void Command_P::reset() {
        Arg* h = firstArg;

        while (h) {
            h->reset();
            h = h->next;
        }
    }

    bool Command_P::parse(String arg, String value) {
        Arg* h = firstArg;

        while (h) {
            if (h->equals(arg)) {
                if (!h->isSet()) {
                    h->setValue(value);
                    return h->isSet();
                }
            }
            h = h->next;
        }
        return false;
    }

    int Command_P::argNum() {
        return args;
    }

    Arg* Command_P::getArg(int i) {
        int  j = 0;
        Arg* h = firstArg;

        while (j < i && h) {
            j++;
            h = h->next;
        }
        return h;
    }

    Arg* Command_P::getArg(const char* name) {
        Arg* h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    Arg* Command_P::getArg(String name) {
        Arg* h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    bool Command_P::isSet(int i) {
        Arg* h = getArg(i);

        return h ? h->isSet() : false;
    }

    bool Command_P::isSet(const char* name) {
        Arg* h = getArg(name);

        return h ? h->isSet() : false;
    }

    bool Command_P::isSet(String name) {
        Arg* h = getArg(name);

        return h ? h->isSet() : false;
    }

    String Command_P::getValue(int i) {
        Arg* h = getArg(i);

        return h ? h->getValue() : String();
    }

    String Command_P::getValue(const char* name) {
        Arg* h = getArg(name);

        return h ? h->getValue() : String();
    }

    String Command_P::getValue(String name) {
        Arg* h = getArg(name);

        return h ? h->getValue() : String();
    }

    void Command_P::addArg(Arg* newArg) {
        if (lastArg) lastArg->next = newArg;

        if (!firstArg) firstArg = newArg;
        lastArg = newArg;
        args++;
    }

    void Command_P::addArg(ReqArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(OptArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(EmptyArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(AnonymReqArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(AnonymOptArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(TemplateReqArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(TemplateOptArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    bool Command_P::isSet() {
        Arg* h = firstArg;

        while (h) {
            if (h->isRequired() && !h->isSet()) return false;

            h = h->next;
        }
        return true;
    }

    void Command_P::addArg(ReqArg_P* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(OptArg_P* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(EmptyArg_P* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(TemplateReqArg_P* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command_P::addArg(TemplateOptArg_P* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    String Command_P::toString() {
        String s;

        s += getName();
        Arg* h = firstArg;

        while (h != NULL) {
            s += ' ';
            s += h->toString();
            h  = h->next;
        }
        return s;
    }
}