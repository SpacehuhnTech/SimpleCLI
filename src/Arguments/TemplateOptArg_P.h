#ifndef TemplateOptArg_P_h
#define TemplateOptArg_P_h

#include "Arg.h"

namespace simpleCLI {
    class TemplateOptArg_P : public Arg {
        public:
            TemplateOptArg_P(const char* _template);
            ~TemplateOptArg_P();

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
#endif // ifndef TemplateOptArg_P_h