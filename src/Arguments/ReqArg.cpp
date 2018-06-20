#include "ReqArg.h"

namespace simpleCLI {
    ReqArg::ReqArg(const char* name) {
        // copy name
        if (name) {
            int strLen = strlen(name);
            ReqArg::name = new char[strLen + 1];
            strcpy(ReqArg::name, name);
            ReqArg::name[strLen] = '\0';
        }

        reset();
    }

    ReqArg::ReqArg(String name) {
        int strLen = name.length() + 1;

        ReqArg::name = new char[strLen];
        name.toCharArray(ReqArg::name, strLen);

        reset();
    }

    ReqArg::~ReqArg() {
        if (name) delete name;

        if (value) delete value;

        if (next) delete next;
    }

    bool ReqArg::equals(const char* name) {
        if (!name) return false;

        if (!ReqArg::name) return false;

        if (name == ReqArg::name) return true;

        return simpleCLI::equals(name, ReqArg::name) >= 0;
    }

    bool ReqArg::equals(String name) {
        return simpleCLI::equals(name.c_str(), ReqArg::name) >= 0;
    }

    void ReqArg::setValue(String value) {
        if (value.length() > 0) {
            if (ReqArg::value) delete ReqArg::value;

            int strLen = value.length() + 1;
            ReqArg::value = new char[strLen];
            value.toCharArray(ReqArg::value, strLen);

            set = true;
        }
    }

    void ReqArg::reset() {
        if (value) {
            delete value;
            value = NULL;
        }

        Arg::reset();
    }

    String ReqArg::getName() {
        return readTemplate(name);
    }

    String ReqArg::getValue() {
        return value ? String(value) : String();
    }

    bool ReqArg::isRequired() {
        return true;
    }

    String ReqArg::toString() {
        return '-' + getName() + ' ' + "<value>";
    }
}