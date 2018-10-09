#ifndef EmptyArg_h
#define EmptyArg_h

#include "Arg.h"

namespace simplecli {
    class EmptyArg : public Arg {
        public:
            EmptyArg(const char* name);
            ~EmptyArg();

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
#endif // ifndef EmptyArg_h