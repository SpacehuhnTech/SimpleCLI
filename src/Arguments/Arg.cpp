#include "Arg.h"

namespace simpleCLI {
    void Arg::reset() {
        set = false;
    }

    String Arg::getName() {
        return String();
    }

    String Arg::getValue() {
        return String();
    }

    bool Arg::isSet() {
        return set;
    }
}