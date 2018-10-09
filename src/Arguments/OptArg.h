#ifndef OptArg_h
#define OptArg_h

#include "Arg.h"

namespace simplecli {
    class OptArg : public Arg {
        public:
            OptArg(const char* name);
            OptArg(const char* name, const char* defaultValue);
            ~OptArg();

            bool equals(const char* name);
            bool equals(String name);
            void setValue(String value);
            void reset();
            String getName();
            String getValue();
            bool isRequired();
            String getDefaultValue();
            String toString();

        private:
            const char* name         = NULL;
            const char* defaultValue = NULL;
            char* value              = NULL;
    };
}

#endif // ifndef OptArg_h