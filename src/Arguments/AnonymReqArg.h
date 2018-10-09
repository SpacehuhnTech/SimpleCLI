#ifndef AnonymReqArg_h
#define AnonymReqArg_h

#include "Arg.h"

namespace simplecli {
    class AnonymReqArg : public Arg {
        public:
            AnonymReqArg();
            ~AnonymReqArg();

            bool equals(const char* name);
            bool equals(String name);
            void setValue(String value);
            void reset();
            String getValue();
            bool isRequired();
            String toString();

        private:
            char* value = NULL;
    };
}
#endif // ifndef AnonymReqArg_h