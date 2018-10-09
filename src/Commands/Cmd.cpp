#include "Cmd.h"

namespace simpleCLI {
    bool Cmd::run(Cmd* cmd) {
        if (runFnct) {
            runFnct(cmd);
            return true;
        }
        return false;
    }
}