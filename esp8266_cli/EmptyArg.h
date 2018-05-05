#ifndef EmptyArg_h
#define EmptyArg_h

#include "Arg.h"

class EmptyArg: public Arg {
  public:
    EmptyArg(const char* name, const char* defaultValue) {
      if (name) {
        int strLen = strlen(name);
        EmptyArg::name = new char[strLen + 1];
        strcpy_P(EmptyArg::name, name);
        EmptyArg::name[strLen] = '\0';
      }
      
      reset();
    }

    EmptyArg(String name) {
      int strLen = name.length() + 1;
      EmptyArg::name = new char[strLen];
      name.toCharArray(EmptyArg::name, strLen);
      reset();
    }

    ~EmptyArg() {
      if(name) delete name;
      if (next) delete next;
    }

    bool equals(const char* name) {
      if(!name) return false;
      if(!EmptyArg::name) return false;
      if(name == EmptyArg::name) return true;

      int strLen;
      strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      return equalsKeyword(tmpName, EmptyArg::name);
    }

    bool equals(String name) {
      return equalsKeyword(name.c_str(), EmptyArg::name);
    }

    void setValue() {
      set = true;
    }

    void setValue(String value) {
      setValue();
    }

    String getName(){
      return name ? String(name) : String();
    }
    
    bool isRequired(){
      return false;
    }
  private:
    char* name = NULL;
};

#endif

