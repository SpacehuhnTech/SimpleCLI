#ifndef TemplateReqArg_h
#define TemplateReqArg_h

#include "Arg.h"

namespace simplecli {
    class TemplateReqArg : public Arg {
        public:
            TemplateReqArg(const char* _template);
            ~TemplateReqArg();

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
#endif // ifndef TemplateReqArg_h