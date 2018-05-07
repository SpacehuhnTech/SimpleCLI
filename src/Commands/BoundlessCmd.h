#ifndef BoundlessCmd_h
#define BoundlessCmd_h

#include "Cmd.h"

class BoundlessCmd: public Cmd {
  public:
    BoundlessCmd(const char* name, void (*runFnct)(Cmd*)){
      BoundlessCmd::runFnct = runFnct;

      if(name){
        int strLen = strlen(name);
        BoundlessCmd::name = new char[strLen+1];
        strcpy(BoundlessCmd::name, name);
        BoundlessCmd::name[strLen] = '\0';
      }
      reset();
    }

    BoundlessCmd(String name, void (*runFnct)(Cmd*)){
      BoundlessCmd::runFnct = runFnct;

      int strLen = name.length()+1;
      BoundlessCmd::name = new char[strLen];
      name.toCharArray(BoundlessCmd::name, strLen);
      reset();
    }

    ~BoundlessCmd(){
      if(name) delete name;
      if(firstArg) delete firstArg;
      if(next) delete next;
    }

    String getName(){
      return String(name);
    }

    void reset(){
      if(firstArg) delete firstArg;
      firstArg = NULL;
      lastArg = NULL;
      args = 0;
    }

    bool parse(String arg, String value){
      bool success = false;

      if(arg.length() > 0){
        Arg* newArg = new AnonymReqArg();
        newArg->setValue(arg);
        if(lastArg) lastArg->next = newArg;
        if(!firstArg) firstArg = newArg;
        lastArg = newArg;
        args++;

        success = true;
      }

      if(value.length() > 0){
        Arg* newArg = new AnonymReqArg();
        newArg->setValue(value);
        if(lastArg) lastArg->next = newArg;
        if(!firstArg) firstArg = newArg;
        lastArg = newArg;
        args++;

        success = true;
      }

      return success;
    }

    int argNum(){
      return args;
    }

    Arg* getArg(int i){
      int j = 0;
      Arg* h = firstArg;
      while(j<i && h){
        j++;
        h = h->next;
      }
      return h;
    }

    Arg* getArg(const char* name){
      Arg* h = firstArg;
      while(h){
        if(h->equals(name))
          return h;
        h = h->next;
      }
      return h;
    }

    Arg* getArg(String name){
      Arg* h = firstArg;
      while(h){
        if(h->equals(name))
          return h;
        h = h->next;
      }
      return h;
    }

    bool isSet(int i){
      Arg* h = getArg(i);
      return h ? h->isSet() : false;
    }

    bool isSet(const char* name){
      Arg* h = getArg(name);
      return h ? h->isSet() : false;
    }

    bool isSet(String name){
      Arg* h = getArg(name);
      return h ? h->isSet() : false;
    }

    String value(int i){
      Arg* h = getArg(i);
      return h ? h->getValue() : String();
    }

    String value(const char* name){
      Arg* h = getArg(name);
      return h ? h->getValue() : String();
    }

    String value(String name){
      Arg* h = getArg(name);
      return h ? h->getValue() : String();
    }

    bool isSet(){
      return true;
    }

  private:
    char* name = NULL;
    int args = 0;
    Arg* firstArg = NULL;
    Arg* lastArg = NULL;
};

#endif
