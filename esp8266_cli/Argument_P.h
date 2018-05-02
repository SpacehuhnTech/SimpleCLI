#ifndef Argument_P_h
#define Argument_P_h

#include "Arg.h"

extern const char EMPTY_PROGMEM_STRING[] PROGMEM;

class Argument_P: public Arg {
  public:
    
    Argument_P(const char* name, const char* defaultValue, bool required) {
      if(!name) name = EMPTY_PROGMEM_STRING;
      if(!defaultValue) defaultValue = EMPTY_PROGMEM_STRING;
      
      Argument_P::name = const_cast<char*>(name);
      Argument_P::defaultValue = const_cast<char*>(defaultValue);
      Argument_P::required = required;
      
      reset();
    }

    ~Argument_P() {
      if (value) delete value;
      if (next) delete next;
    }

    bool equals(const char* name) {
      if(!name) return false;
      if(name == Argument_P::name) return true;
      
      int strLen;

      strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      strLen = strlen_P(Argument_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, Argument_P::name);
      tmpKeyword[strLen] = '\0';

      return equalsKeyword(tmpName, tmpKeyword);
    }

    bool equals(String name) {
      int strLen = strlen_P(Argument_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, Argument_P::name);
      tmpKeyword[strLen] = '\0';

      return equalsKeyword(name.c_str(), tmpKeyword);
    }

    void setValue(String value) {
      if (Argument_P::value) delete Argument_P::value;

      int strLen = value.length() + 1;
      Argument_P::value = new char[strLen];
      value.toCharArray(Argument_P::value, strLen);

      set = true;
    }

    void reset() {
      if (value) delete value;
      
      int strLen = strlen_P(defaultValue);
      value = new char[strLen + 1];
      strcpy_P(value, defaultValue);
      value[strLen] = '\0';
      
      set = false;
    }
};

#endif

