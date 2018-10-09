#include "Arg.h"

namespace simplecli {
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
