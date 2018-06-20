#include "ReqArg_P.h"

namespace simpleCLI {
    ReqArg_P::ReqArg_P(const char* name) {
        ReqArg_P::name = name;
    }

    ReqArg_P::~ReqArg_P() {
        if (value) delete value;

        if (next) delete next;
    }

    bool ReqArg_P::equals(const char* name) {
        if (!name) return false;

        if (!ReqArg_P::name) return false;

        if (name == ReqArg_P::name) return true;

        int strLen;
        strLen = strlen_P(name);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, name);
        tmpName[strLen] = '\0';

        strLen = strlen_P(ReqArg_P::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, ReqArg_P::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(tmpName, tmpKeyword) >= 0;
    }

    bool ReqArg_P::equals(String name) {
        if (!ReqArg_P::name) return false;

        int  strLen = strlen_P(ReqArg_P::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, ReqArg_P::name);
        tmpKeyword[strLen] = '\0';

        return simpleCLI::equals(name.c_str(), tmpKeyword) >= 0;
    }

    void ReqArg_P::setValue(String value) {
        if (value.length() > 0) {
            if (ReqArg_P::value) delete ReqArg_P::value;

            int strLen = value.length() + 1;
            ReqArg_P::value = new char[strLen];
            value.toCharArray(ReqArg_P::value, strLen);

            set = true;
        }
    }

    void ReqArg_P::reset() {
        if (value) {
            delete value;
            value = NULL;
        }

        Arg::reset();
    }

    String ReqArg_P::getName() {
        return readTemplate(name);
    }

    String ReqArg_P::getValue() {
        return value ? String(value) : String();
    }

    bool ReqArg_P::isRequired() {
        return true;
    }

    String ReqArg_P::toString() {
        return '-' + getName() + ' ' + "<value>";
    }
}