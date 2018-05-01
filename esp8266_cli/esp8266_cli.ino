#include "Argument.h"
#include "Argument_P.h"
#include "Command.h"
#include "Command_P.h"

#include "CommandParser.h"

extern "C" {
  #include "user_interface.h"
}

const char CLI_NULL[] PROGMEM = " ";

const char CLI_PING[] PROGMEM = "p,ping/s";
const char CLI_PONG[] PROGMEM = "pong!";
const char CLI_LINE[] PROGMEM = "l,line";
const char CLI_NUM[] PROGMEM = "n,number";
const char CLI_STR[] PROGMEM = "s,str/ing";

const char CLI_RAM[] PROGMEM = "ram";

CommandParser* cli;

void setup() {
  Serial.begin(115200);

  Serial.printf(String(F("RAM usage: %u bytes used [%d%%], %u bytes free [%d%%], %u bytes in total\r\n")).c_str(), 81920 - system_get_free_heap_size(), 100 - system_get_free_heap_size() / (81920 / 100), system_get_free_heap_size(), system_get_free_heap_size() / (81920 / 100), 81920);
  cli = new CommandParser();

  cli->onNotFound = [](String cmdName){
    Serial.println(cmdName+" not found");  
  };

   for(int i=0;i<100;i++){
    
    Cmd* test = new Command("test",[](Cmd* cmd){
      Serial.println(String(F("test")));
    },[](uint8_t error){
      Serial.println(String(F("test")));
    });
    //delete test;
    cli->addCommand(test);/*
    Cmd* test2 = new Command_P(CLI_NULL,[](Cmd* cmd){
      Serial.println("test");
    },[](uint8_t error){
      Serial.println("test");
    });
    test2->next = test;
    delete test2;*/
  }
  
  Command_P* ping = new Command_P(CLI_PING,[](Cmd* command){
    Command_P* cmd = static_cast<Command_P*>(command);
    int h = cmd->value_P(CLI_NUM).toInt();
    
    if(cmd->has_P(CLI_LINE)){
      for(int i=0; i<h; i++){
        Serial.println(cmd->value_P(CLI_STR));
      }
    }else{
      for(int i=0; i<h; i++){
        Serial.print(cmd->value_P(CLI_STR));
      }
    }
    Serial.println();
  },[](uint8_t error){
    //Serial.print(error);
    Serial.println(String(F("Something went wrong. Did you mean: \"ping -n <num> [-s <str>] [-l]\"?")));
  });
  ping->addOptArg_P(CLI_LINE, CLI_NULL);
  ping->addOptArg_P(CLI_STR, CLI_PONG);
  ping->addReqArg_P(CLI_NUM, CLI_NULL);
  cli->addCommand(ping);

  cli->addCommand(new Command_P(CLI_RAM, [](Cmd* cmd){
    Serial.printf(String(F("RAM usage: %u bytes used [%d%%], %u bytes free [%d%%], %u bytes in total\r\n")).c_str(), 81920 - system_get_free_heap_size(), 100 - system_get_free_heap_size() / (81920 / 100), system_get_free_heap_size(), system_get_free_heap_size() / (81920 / 100), 81920);
  }, NULL ));

  Serial.printf(String(F("RAM usage: %u bytes used [%d%%], %u bytes free [%d%%], %u bytes in total\r\n")).c_str(), 81920 - system_get_free_heap_size(), 100 - system_get_free_heap_size() / (81920 / 100), system_get_free_heap_size(), system_get_free_heap_size() / (81920 / 100), 81920);

  cli->parse("ping");
  cli->parse("ping -n 11");
  cli->parse("ping -n 11 -s test");
}

void loop() {
  if (Serial.available()) cli->parse(Serial.readStringUntil('\n'));
}
