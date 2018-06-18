#ifndef OptArg_P_h
#define OptArg_P_h

#include "Arg.h"

namespace arduino_cli {
    class OptArg_P : public Arg {
        public:
            OptArg_P(const char* name, const char* defaultValue);
            ~OptArg_P();

            bool equals(const char* name);
            bool equals(String name);
            void setValue(String value);
            void reset();
            String getName();
            String getValue();
            bool isRequired();
            String toString();

        private:
            const char* name         = NULL;
            const char* defaultValue = NULL;
            char* value              = NULL;
    };
}

#endif // ifndef OptArg_P_h