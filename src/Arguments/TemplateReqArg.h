#ifndef TemplateReqArg_h
#define TemplateReqArg_h

#include "Arg.h"

namespace arduino_cli {
    class TemplateReqArg : public Arg {
        public:
            TemplateReqArg(const char *_template);
            TemplateReqArg(String _template);
            ~TemplateReqArg();

            bool equals(const char *name);
            bool equals(String name);
            void setValue(String value);
            void reset();
            String getValue();
            bool isRequired();
            int getValueIndex();

        private:
            char *value     = NULL;
            char *_template = NULL;
            int index       = -1;
    };
}
#endif // ifndef TemplateReqArg_h