#include "ReqArg.h"

namespace simplecli {
    ReqArg::ReqArg(const char* name) {
        this->name = name;
    }

    ReqArg::~ReqArg() {
        if (value) delete value;

        if (next) delete next;
    }

    bool ReqArg::equals(const char* name) {
        if (!name) return false;

        if (!ReqArg::name) return false;

        if (name == ReqArg::name) return true;

        int strLen;
        strLen = strlen_P(name);
        char tmpName[strLen + 1];
        strcpy_P(tmpName, name);
        tmpName[strLen] = '\0';

        strLen = strlen_P(ReqArg::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, this->name);
        tmpKeyword[strLen] = '\0';

        return simplecli::equals(tmpName, tmpKeyword) >= 0;
    }

    bool ReqArg::equals(String name) {
        if (!this->name) return false;

        int  strLen = strlen_P(ReqArg::name);
        char tmpKeyword[strLen + 1];
        strcpy_P(tmpKeyword, this->name);
        tmpKeyword[strLen] = '\0';

        return simplecli::equals(name.c_str(), tmpKeyword) >= 0;
    }

    void ReqArg::setValue(String value) {
        if (value.length() > 0) {
            if (this->value) delete this->value;

            int strLen = value.length() + 1;
            this->value = new char[strLen];
            value.toCharArray(this->value, strLen);

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
