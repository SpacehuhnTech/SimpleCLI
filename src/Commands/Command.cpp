#include "Command.h"

namespace simplecli {
    Command::Command(const char* name, CmdRunFunction) {
        this->runFnct = runFnct;
        this->name    = name;

        reset();
    }

    Command::~Command() {
        if (firstArg) delete firstArg;

        if (next) delete next;
    }

    String Command::getName() {
        return readTemplate(name);
    }

    void Command::reset() {
        Arg* h = firstArg;

        while (h) {
            h->reset();
            h = h->next;
        }
    }

    bool Command::parse(String arg, String value) {
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

    int Command::argNum() {
        return args;
    }

    Arg* Command::getArg(int i) {
        int  j = 0;
        Arg* h = firstArg;

        while (j < i && h) {
            j++;
            h = h->next;
        }
        return h;
    }

    Arg* Command::getArg(const char* name) {
        Arg* h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    Arg* Command::getArg(String name) {
        Arg* h = firstArg;

        while (h) {
            if (h->equals(name)) return h;

            h = h->next;
        }
        return h;
    }

    bool Command::isSet(int i) {
        Arg* h = getArg(i);

        return h ? h->isSet() : false;
    }

    bool Command::isSet(const char* name) {
        Arg* h = getArg(name);

        return h ? h->isSet() : false;
    }

    bool Command::isSet(String name) {
        Arg* h = getArg(name);

        return h ? h->isSet() : false;
    }

    String Command::getValue(int i) {
        Arg* h = getArg(i);

        return h ? h->getValue() : String();
    }

    String Command::getValue(const char* name) {
        Arg* h = getArg(name);

        return h ? h->getValue() : String();
    }

    String Command::getValue(String name) {
        Arg* h = getArg(name);

        return h ? h->getValue() : String();
    }

    void Command::addArg(Arg* newArg) {
        if (lastArg) lastArg->next = newArg;

        if (!firstArg) firstArg = newArg;
        lastArg = newArg;
        args++;
    }

    void Command::addArg(ReqArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command::addArg(OptArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command::addArg(EmptyArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command::addArg(AnonymReqArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command::addArg(AnonymOptArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command::addArg(TemplateReqArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    void Command::addArg(TemplateOptArg* newArg) {
        addArg(static_cast<Arg*>(newArg));
    }

    bool Command::isSet() {
        Arg* h = firstArg;

        while (h) {
            if (h->isRequired() && !h->isSet()) return false;

            h = h->next;
        }
        return true;
    }

    String Command::toString() {
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