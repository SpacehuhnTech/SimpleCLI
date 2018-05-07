#ifndef EmptyCmd_P_h
#define EmptyCmd_P_h

#include "Cmd.h"

class EmptyCmd_P: public Cmd {
  public:
    EmptyCmd_P(const char* name, void (*runFnct)(Cmd*)){
      EmptyCmd_P::runFnct = runFnct;
      
      EmptyCmd_P::name = name;
      reset();
    }
    
    ~EmptyCmd_P(){
      if(next) delete next;
    }
    
    String getName(){
       int strLen = strlen_P(name);
      char tmpName[strLen+1];
      strcpy_P(tmpName, name);
      tmpName[strLen] = '\0';
      return String(tmpName);
    }
    
    void reset(){
      
    }
    
    bool parse(String arg, String value){
      return true;
    }
    
    int argNum(){
      return 0;
    }
    
    Arg* getArg(int i){
      return NULL;
    }
    
    Arg* getArg(const char* name){
      return NULL;
    }
    
    Arg* getArg(String name){
      return NULL;
    }

    bool isSet(int i){
      return false;
    }
    
    bool isSet(const char* name){
      return false;
    }
    
    bool isSet(String name){
      return false;
    }
    
    String value(int i){
      return String();
    }
    
    String value(const char* name){
      return String();
    }
    
    String value(String name){
      return String();
    }
    
    bool isSet(){
      return true;
    }
    
  private:
    const char* name = NULL;
};

#endif

