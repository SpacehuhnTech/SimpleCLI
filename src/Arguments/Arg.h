#ifndef Arg_h
#define Arg_h

#include "Arduino.h"
#include "helper_functions.h"

namespace simplecli {
    class Arg {
        public:
            Arg* next = NULL;

            virtual ~Arg() = default;

            virtual void setValue(String value)   = 0;
            virtual bool equals(String name)      = 0;
            virtual bool equals(const char* name) = 0;
            virtual bool isRequired()             = 0;

            virtual String toString() = 0;

            virtual void reset();

            virtual String getName();
            virtual String getValue();

            virtual bool isSet();

        protected:
            bool set = false;
    };
}
#endif // ifndef Arg_h
