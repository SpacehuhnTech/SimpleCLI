#ifndef AnonymOptArg_h
#define AnonymOptArg_h

#include "Arg.h"

namespace arduino_cli {
    class AnonymOptArg : public Arg {
        public:
            AnonymOptArg(const char *defaultValue);
            AnonymOptArg(String defaultValue);
            ~AnonymOptArg();

            bool equals(const char *name);
            bool equals(String name);
            void setValue(String value);
            void reset();
            String getValue();
            bool isRequired();

        private:
            char *value        = NULL;
            char *defaultValue = NULL;
    };
}
#endif // ifndef AnonymOptArg_h
