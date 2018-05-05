#ifndef EmptyArg_P_h
#define EmptyArg_P_h

#include "Arg.h"

class EmptyArg_P: public Arg {
  public:
    EmptyArg_P(const char* name) {
      EmptyArg_P::name = name;
      
      reset();
    }

    ~EmptyArg_P() {
      if (next) delete next;
    }

    bool equals(const char* name) {
      if(!name) return false;
      if(!EmptyArg_P::name) return false;
      if(name == EmptyArg_P::name) return true;

      int strLen;
      strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';

      strLen = strlen_P(EmptyArg_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, EmptyArg_P::name);
      tmpKeyword[strLen] = '\0';

      return equalsKeyword(tmpName, tmpKeyword);
    }

    bool equals(String name) {
      if(!EmptyArg_P::name) return false;
      
      int strLen = strlen_P(EmptyArg_P::name);
      char tmpKeyword[strLen + 1];
      strcpy_P(tmpKeyword, EmptyArg_P::name);
      tmpKeyword[strLen] = '\0';

      return equalsKeyword(name.c_str(), tmpKeyword);
    }

    void setValue() {
      set = true;
    }

    void setValue(String value) {
      setValue();
    }
    
    String getName(){
      if(!name) return String();
      
      int strLen = strlen_P(name);
      char tmpName[strLen + 1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';
      
      return String(tmpName);
    }

    bool isRequired(){
      return false;
    }

  private:
    const char* name = NULL;
};

#endif

