#include "Cmd.h"

namespace simplecli {
    bool Cmd::run(Cmd* cmd) {
        if (runFnct) {
            runFnct(cmd);
            return true;
        }
        return false;
    }
}