#ifndef TemplateReqArg_P_h
#define TemplateReqArg_P_h

#include "Arg.h"

namespace simpleCLI {
    class TemplateReqArg_P : public Arg {
        public:
            TemplateReqArg_P(const char* _template);
            ~TemplateReqArg_P();

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
#endif // ifndef TemplateReqArg_P_h