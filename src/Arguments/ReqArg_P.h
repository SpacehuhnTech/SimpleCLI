#ifndef ReqArg_P_h
#define ReqArg_P_h

#include "Arg.h"

namespace arduino_cli {
    class ReqArg_P : public Arg {
        public:
            ReqArg_P(const char *name);
            ~ReqArg_P();

            bool equals(const char *name);
            bool equals(String name);
            void setValue(String value);
            void reset();
            String getName();
            String getValue();
            bool isRequired();

        private:
            const char *name = NULL;
            char *value      = NULL;
    };
}

#endif // ifndef ReqArg_P_h