#ifndef TemplateOptArg_h
#define TemplateOptArg_h

#include "Arg.h"

namespace simplecli {
    class TemplateOptArg : public Arg {
        public:
            TemplateOptArg(const char* _template);
            ~TemplateOptArg();

            bool equals(const char* name);
            bool equals(String name);
            void setValue(String value);
            void reset();
            String getValue();
            bool isRequired();
            int getValueIndex();
            String toString();

        private:
            char* value           = NULL;
            const char* _template = NULL;
            int index             = -1;
    };
}
#endif // ifndef TemplateOptArg_h