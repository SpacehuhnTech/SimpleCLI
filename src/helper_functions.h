#ifndef helper_functions_h
#define helper_functions_h

namespace simplecli {
    static bool caseSensetive = false;

    inline int equals(const char* str, const char* keyword) {
        // null check string pointers
        if (!str || !keyword) return -3;

        // count strings
        int lenStr     = strlen(str);
        int lenKeyword = strlen(keyword);

        // when same length, it there is no need to check for slashes or commas
        if (lenStr == lenKeyword) {
            for (int i = 0; i < lenKeyword; i++) {
                if (simplecli::caseSensetive) {
                    if (str[i] != keyword[i]) return -1;
                } else {
                    if (tolower(str[i]) != tolower(keyword[i])) return -1;
                }
            }
            return 0;
        }

        // string can't be longer than keyword (but can be smaller because of  '/' and ',')
        if (lenStr > lenKeyword) return -2;

        int  resIndex = 0;
        int  a        = 0;
        int  b        = 0;
        bool result   = true;

        while (a < lenStr && b < lenKeyword) {
            if (keyword[b] == '/') {
                // skip slash in keyword
                b++;
            } else if (keyword[b] == ',') {
                // on comma increment resIndex and reset str-index
                b++;
                a = 0;
                resIndex++;
            }

            // compare character
            if (simplecli::caseSensetive) {
                if (str[a] != keyword[b]) result = false;
            } else {
                if (tolower(str[a]) != tolower(keyword[b])) result = false;
            }

            // comparison incorrect or string checked until the end and keyword not checked until the end
            if (!result || ((a == lenStr - 1) && (keyword[b + 1] != ',') &&
                            (keyword[b + 1] != '/') && (keyword[b + 1] != '\0'))) {
                // fast forward to next comma
                while (b < lenKeyword && keyword[b] != ',') b++;
                result = true;
            } else {
                // otherwise icrement indices
                a++;
                b++;
            }
        }

        // comparison correct AND string checked until the end AND keyword checked until the end
        if (result && (a == lenStr) &&
            ((keyword[b] == ',') || (keyword[b] == '/') ||
             (keyword[b] == '\0'))) return resIndex;
        else return -1;
    }

    inline String readTemplate(const char* _template) {
        if (_template == NULL) return String();

        String s = String(_template);

        s.replace("/", "");

        return s;
    }
}

#endif // ifndef helper_functions_h