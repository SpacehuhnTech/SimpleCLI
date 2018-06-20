#ifndef EmptyArg_P_h
#define EmptyArg_P_h

#include "Arg.h"

namespace simpleCLI {
    class EmptyArg_P : public Arg {
        public:
            EmptyArg_P(const char* name);
            ~EmptyArg_P();

            bool equals(const char* name);
            bool equals(String name);
            void setValue();
            void setValue(String value);
            String getName();
            bool isRequired();
            String toString();

        private:
            const char* name = NULL;
    };
}
#endif // ifndef EmptyArg_P_h
