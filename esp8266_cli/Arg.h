#ifndef Arg_h
#define Arg_h

class Arg {
  public:
    Arg* next = NULL;

    virtual ~Arg() = default;

    virtual void setValue(String value) = 0;
    virtual void reset() = 0;
    virtual bool equals(const char* name) = 0;

    bool equals_P(const char* name) {
      return name == Arg::name;
    }
    
    String getName() {
      return String(name);
    }

    const char* getNamePtr() {
      return name;
    }

    String getValue() {
      return String(value);
    }

    bool isSet() {
      return set;
    }

    bool isRequired() {
      return required;
    }

  protected:
    char* name = NULL;
    char* defaultValue = NULL;
    char* value = NULL;
    bool set = false;
    bool required = false;

    bool equalsKeyword(const char* str, const char* keyword) {
      if (!str) return false;
      if (!keyword) return false;

      int lenStr = strlen(str);
      int lenKeyword = strlen(keyword);

      // string can't be longer than keyword (but can be smaller because of '/' and ',')
      if (lenStr > lenKeyword)
        return false;

      if (lenStr == lenKeyword)
        return strcmp(str, keyword) == 0;

      int a = 0;
      int b = 0;
      bool result = true;

      while (a < lenStr && b < lenKeyword) {
        if (keyword[b] == '/') {
          b++;
        } else if (keyword[b] == ',') {
          b++;
          a = 0;
          result = true;
        }

        if (tolower(str[a]) != tolower(keyword[b])) {
          result = false;
        }

        // fast forward to next comma
        if ((a == lenStr && !result) || !result) {
          while (++b < lenKeyword && keyword[b] != ',');
        } else {
          a++;
          b++;
        }
      }

      // comparison correct AND string checked until the end AND keyword checked until the end
      result = result && a == lenStr && (keyword[b] == ',' || keyword[b] == '/' || keyword[b] == '\0');
      return result;
    }
};

#endif

