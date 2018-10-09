# Command Line Interface Library for Arduino
Control your Arduino devices with custom commands without much hassle!  

## About
This library goal is to make it easy to add custom commands, with arguments and all that sweet stuff, to your Arduino projects!  
Because there are multiple ways of how you can define the syntax of each command, there are different types of commands and arguments provided by this library.  

Please note that the library is written for the ESP8266 and ESP32. Other platforms might not work without modifications.  

**See the [Examples](https://github.com/spacehuhn/Arduino_CLI/tree/master/examples/) on how to use the different Commands and Arguments.** (not finished yet)  

## Installation

1) [Download](https://github.com/spacehuhn/SimpleCLI/archive/master.zip) the source code from GitHub.  
2) Unzip and rename the Folder name to "SimpleCLI".  
3) Paste it in your Library folder (Usually located somewhere at documents/Arduino/libraries).  
4) Restart the Arduino IDE.  

### Include & namespace

To make use of the library in your Arduino sketch, you have to include it:  

```
#include <SimpleCLI.h>

using namespace simplecli;
```

### Commands

| Class Name | Info | When to use |
| ---------- | ---- | ----------- |
| Command | Parses arguments and only runs if all required arguments were given. | For commands with >= 1 arguments. |
| EmptyCmd | Saves no arguments. | For commands that don't need any arguments. |
| BoundlessCmd | Saves user input after command name into a list of arguments. | When it doesn't matter what the user types after the command name, but you need it as a list of arguments. |
| SingleArgCmd | Saves user input after command name into a single of argument value. | When it doesn't matter what the user types after the command name, but you need it as one string. |

Create a new command:  
```
Cmd* myCommand = new Command("commandName", [](Cmd* myCommand){
  // do something
})
```

Create a new command using progmem strings:  
```
const char CMD_NAME[] PROGMEM = "commandName";

Cmd* myCommand = new Command(CMD_NAME, [](Cmd* myCommand){
  // do something
})
```

### Arguments

| Class Name | Constructor | Mode | Info | Example |
| ---------- | ----------- |----- | ---- | ----------- |
| AnonymOptArg | (const char* defaultValue) | Optional | Has no name, but a default value. | `echo`, `echo something` |
| AnonymReqArg | (void) | Required | Has no name. Value must be given by the user. | `rm somefile` |
| EmptyArg | (const char* name, const char* defaultValue) | Optional | Doesn't take any value. Can either be set or not. | `ls`, `ls -a` |
| OptArg | (const char* name, const char* defaultValue) | Optional | Has a default value. |  `ping`, `ping -s 2048` |
| ReqArg | (const char* name) | Required | Value must be given by the user. | `myScript.sh -o output.txt` |
| TemplateOptArg | (const char* template) | Optional | Can take different names, the first name is the default one. Has no value. | `scan`, `scan aps`, `scan stations` |
| TemplateReqArg | (const char* template) | Required | Can take different names. Has no value. | `remove aps`, `remove stations` |

Create an argument:  
```
Arg* myArg = new OptArg("name", "world");
```

Create an argument using progmeme strings:  
```
const char ARG_NAME[] PROGMEM = "name";
const char ARG_VALUE[] PROGMEM = "world";

Arg* myArg = new OptArg(ARG_NAME, ARG_VALUE);
```

### Templates

With a little trick, this library enables you to give a command or argument multiple names.  
- A comma (`,`) separates multiple names.  
- A forward slash (`/`) declares that everything after it is optional (until the next comma, or the end of the string).  

You can combine them together.  

**This means a command or argument name should not use `,` and `/` as a part of the regular name!**  
These characters will always be interpreted as a separator.  

Here are some examples:  

| Name-String | Results |
| ----------- | ------- |
| `a,b,c,d,efg` | `a`, `b`, `c`, `d`, `efg` |
| `ping,pong,test` | `ping`, `pong`, `test` |
| `p/ping` | `p`, `ping` |
| `p/ing/s` | `p`, `ping`, `pings` |
| `p/ing/s,pong` | `p`, `ping`, `pings`, `pong` |
| `p/ing/s,pong/s` | `p`, `ping`, `pings`, `pong`, `pongs` |

If you use the `templateReqArg` or `templateOptArg`, it will check at which index (comma separated) the input is.  
For example, an argument named `ping,pong` will check that the user types in `ping` **or** `pong`.
The method `getValueIndex()` will return a `0` if the input was `ping` and `1` if the input was `pong`.  
For more details on this, look at the  [Examples](https://github.com/spacehuhn/Arduino_CLI/tree/master/examples/).  
