# Command Line Interface Library for Arduino
Control your Arduino devices with custom commands without much hazzle!  

## About
This library goal is to make it easy to add custom commands, with arguments and all that sweet stuff, to your Arduino projects!  
Because there are multiple ways of how can define the syntax of each command, there are different types of commands and arguments provided by this library.  

### Commands

| Class Name | Info | When to use |
| ---------- | ---- | ----------- |
| Command | Parses arguments and only runs if all required arguments were given. | For commands with >= 1 arugments. |
| EmptyCmd | Saves no arguments. | For commands that don't need any arguments. |
| BoundlessCmd | Saves user input after command name into a list of arguments. | When it doesn't matter what the user types after the command name, but you need it as a list of arguments. |
| SingleArgCmd | Saves user input after command name into a single of argument value. | When it doesn't matter what the user types after the command name, but you need it as one string. |

You can create a new command by:  
```
Cmd* myCommand = new Command("commandName", [](Cmd* myCommand){
  // do something
})
```

To save RAM, the same command classes exist but using progmem strings instead of regular strings.  

| Class Name | Info | When to use |
| ---------- | ---- | ----------- |
| Command_P | See table above | See table above |
| EmptyCmd_P | See table above | See table above |
| BoundlessCmd_P | See table above | See table above |
| SingleArgCmd_P | See table above | See table above |

You can create a new progmem command by:  
```
const char CMD_NAME[] PROGMEM = "commandName";

...

Cmd* myCommand = new Command_P(CMD_NAME, [](Cmd* myCommand){
  // do something
})
```

### Arguments

| Class Name | Constructor | Info | When to use |
| ---------- | ----------- | ---- | ----------- |
| AnonymOptArg | | | |
| AnonymReqArg | | | |
| EmptyArg | | | |
| OptArg | | | |
| ReqArg | | | |
| TemplateOptArg | | | |
| TemplateReqArg | | | |

| Class Name | Constructor | Info | When to use |
| ---------- | ----------- | ---- | ----------- |
| AnonymOptArg_P | See table above | See table above | See table above |
| AnonymReqArg_P | See table above | See table above | See table above |
| EmptyArg_P | See table above | See table above | See table above |
| OptArg_P | See table above | See table above | See table above |
| ReqArg_P | See table above | See table above | See table above |
| TemplateOptArg_P | See table above | See table above | See table above |
| TemplateReqArg_P | See table above | See table above | See table above |
