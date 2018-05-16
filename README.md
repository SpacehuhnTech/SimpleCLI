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

| Class Name |
| ---------- |
| Command_P |
| EmptyCmd_P |
| BoundlessCmd_P |
| SingleArgCmd_P |

You can create a new progmem command by:  
```
const char CMD_NAME[] PROGMEM = "commandName";

...

Cmd* myCommand = new Command_P(CMD_NAME, [](Cmd* myCommand){
  // do something
})
```

### Arguments

| Class Name | Constructor | Info | Example |
| ---------- | ----------- | ---- | ----------- |
| AnonymOptArg | defaultValue | Has no name, but a default value. | `echo`, `echo something` |
| AnonymReqArg | | Has no name. Value must be given by the user. | `rm somefile` |
| EmptyArg | name, defaultValue | Doesn't take any value. | ` ` |
| OptArg | name, defaultValue | Optional Argument. Has a default value. |  `ping`, `ping -s 2048` |
| ReqArg | name | Required Argument. Value must be given by the user. | ` ` |
| TemplateOptArg | template | | |
| TemplateReqArg | template | | |

| Class Name |
| ---------- |
| AnonymOptArg_P |
| AnonymReqArg_P |
| EmptyArg_P |
| OptArg_P |
| ReqArg_P |
| TemplateOptArg_P |
| TemplateReqArg_P |
