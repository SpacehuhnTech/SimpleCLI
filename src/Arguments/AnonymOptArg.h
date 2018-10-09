#ifndef AnonymOptArg_h
#define AnonymOptArg_h

#include "Arg.h"

namespace simplecli {
    class AnonymOptArg : public Arg {
        public:
            AnonymOptArg();
            AnonymOptArg(const char* defaultValue);
            ~AnonymOptArg();

            bool   equals(const char* name);
            bool   equals(String name);
            void   setValue(String value);
            void   reset();
            String getValue();
            bool   isRequired();
            String getDefaultValue();
            String toString();

        private:
            char* value              = NULL;
            const char* defaultValue = NULL;
    };
}
#endif /* ifndef AnonymOptArg_h */