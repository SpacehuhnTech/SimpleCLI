#ifndef AnonymOptArg_P_h
#define AnonymOptArg_P_h

#include "Arg.h"

namespace arduino_cli {
    class AnonymOptArg_P : public Arg {
        public:
            AnonymOptArg_P(const char *defaultValue);
            ~AnonymOptArg_P();

            bool   equals(const char *name);
            bool   equals(String name);
            void   setValue(String value);
            void   reset();
            String getValue();
            bool   isRequired();

        private:
            char *value              = NULL;
            const char *defaultValue = NULL;
    };
}
#endif /* ifndef AnonymOptArg_P_h */
