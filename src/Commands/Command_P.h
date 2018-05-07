#ifndef Command_P_h
#define Command_P_h

#include "Cmd.h"

class Command_P: public Cmd {
  public:
    Command_P(const char* name, void (*runFnct)(Cmd*)){
      Command_P::runFnct = runFnct;

      Command_P::name = name;
      reset();
    }

    ~Command_P(){
      if(firstArg) delete firstArg;
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
      Arg* h = firstArg;
      while(h){
        h->reset();
        h = h->next;
      }
    }

    bool parse(String arg, String value){
      Arg* h = firstArg;
      while(h){
        if(h->equals(arg)){
          if(!h->isSet()){
            h->setValue(value);
            return h->isSet();
          }
        }
        h = h->next;
      }
      return false;
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

    void addArg(Arg* newArg){
      if(lastArg) lastArg->next = newArg;
      if(!firstArg) firstArg = newArg;
      lastArg = newArg;
      args++;
    }

    void addArg(ReqArg* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(ReqArg_P* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(OptArg* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(OptArg_P* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(EmptyArg* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(EmptyArg_P* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(AnonymReqArg* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(AnonymOptArg* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(AnonymOptArg_P* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(TemplateReqArg* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(TemplateReqArg_P* newArg){ addArg(static_cast<Arg*>(newArg)); }
    void addArg(TemplateOptArg* newArg){addArg( static_cast<Arg*>(newArg)); }
    void addArg(TemplateOptArg_P* newArg){ addArg(static_cast<Arg*>(newArg)); }

    bool isSet(){
      Arg* h = firstArg;
      while(h){
        if(h->isRequired() && !h->isSet())
          return false;
        h = h->next;
      }
      return true;
    }

  private:
    const char* name = NULL;
    int args = 0;
    Arg* firstArg = NULL;
    Arg* lastArg = NULL;
};

#endif
