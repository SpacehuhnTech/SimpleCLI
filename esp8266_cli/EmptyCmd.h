#ifndef EmptyCmd_h
#define EmptyCmd_h

#include "Cmd.h"

class EmptyCmd: public Cmd {
  public:
    EmptyCmd(const char* name, void (*runFnct)(Cmd*)){
      EmptyCmd::runFnct = runFnct;
      
      if(name){
        int strLen = strlen_P(name);
        EmptyCmd::name = new char[strLen+1];
        strcpy_P(EmptyCmd::name, name);
        EmptyCmd::name[strLen] = '\0';
      }
      reset();
    }
    
    EmptyCmd(String name, void (*runFnct)(Cmd*)){
      EmptyCmd::runFnct = runFnct;
      
      int strLen = name.length()+1;
      EmptyCmd::name = new char[strLen];
      name.toCharArray(EmptyCmd::name, strLen);
      reset();
    }
    
    ~EmptyCmd(){
      if(name) delete name;
      if(next) delete next;
    }
    
    String getName(){
      return String(name);
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
    char* name = NULL;
};

#endif

