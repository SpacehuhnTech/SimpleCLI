# Command Line Interface Library for Arduino
Control your Arduino devices with custom commands without much hazzle!  

## About
This library goal is to make it easy to add custom commands, with arguments and all that sweet stuff, to your Arduino projects!  
Because there are multiple ways of how can define the syntax of each command, there are different types of commands and arguments provided by this library.  

**See the [Examples](https://github.com/spacehuhn/Arduino_CLI/tree/master/examples/) on how to use the different Commands and Arguments.**  

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

To save RAM, the same command classes exist with progmem strings instead of regular strings.  

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
| AnonymOptArg | defaultValue | [Optional] Has no name, but a default value. | `echo`, `echo something` |
| AnonymReqArg | defaultValue | [Required] Has no name. Value must be given by the user. | `rm somefile` |
| EmptyArg | name, defaultValue | [Optional] Doesn't take any value. Can either be set or not. | `ls`, `ls -a` |
| OptArg | name, defaultValue | [Optional] Has a default value. |  `ping`, `ping -s 2048` |
| ReqArg | name | [Required] Value must be given by the user. | `myScript.sh -o output.txt` |
| TemplateOptArg | template | [Optional] Can take different names, the first name is the default one. Has no value. | `scan`, `scan aps`, `scan stations` |
| TemplateReqArg | template | [Required] Can take different names. Has no value. | `remove aps`, `remove stations` |

You can create a new argument by:  
```
Arg* myArg = new OptArg("name", "world");
```

To save RAM, the same argument classes exist with progmem strings instead of regular strings.  

| Class Name |
| ---------- |
| AnonymOptArg_P |
| AnonymReqArg_P |
| EmptyArg_P |
| OptArg_P |
| ReqArg_P |
| TemplateOptArg_P |
| TemplateReqArg_P |

You can create a new progmem argument by:  
```
const char ARG_NAME[] PROGMEM = "name";
const char ARG_VALUE[] PROGMEM = "world";

...

Arg* myArg = new OptArg_P(ARG_NAME, ARG_VALUE);
```

### Templates

With a little trick, this library enables you to give a command or argument multiple names.  
- A comma `,` seperates multiple names.  
- The `/` declares everything after it as optional (until the next comma, or the end of the string).  

You can also combine those together.  

**This means you can not use `,` and `/` inside a command or argument name!**  
These characters will always be interpreted as a seperator!  

Here are some examples:  

| Name-String | Results |
| ----------- | ------- |
| `a,b,c,d,efg` | `a`, `b`, `c`, `d`, `efg` |
| `ping,pong,test` | `ping`, `pong`, `test` |
| `p/ping` | `p`, `ping` |
| `p/ing/s` | `p`, `ping`, `pings` |
| `p/ing/s,pong` | `p`, `ping`, `pings`, `pong` |
| `p/ing/s,pong/s` | `p`, `ping`, `pings`, `pong`, `pongs` |

If you use the `templateReqArg` or `templateOptArg`, it will check at which index (comma seperated) the input is.  
For example, an argument named `ping,pong` will check that the user types in `ping` **or** `pong`. The method `getValueIndex()` will return a `0` if the input was `ping` and `1` if the input was `pong`.  
For more details on this, look at the  [Examples](https://github.com/spacehuhn/Arduino_CLI/tree/master/examples/).  
