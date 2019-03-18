/*
   Copyright (c) 2019 Stefan Kremser
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/SimpleCLI
 */

/*
   This is an example with all types of arguments and commands, error check and help command.
   No callbacks are used here, you can check the callback example for that.

   PLEASE NOTE: 115200 is the baud rate and Newline is enabled in the serial monitor
 */

// Inlcude Library
#include <SimpleCLI.h>

// Create CLI Object
SimpleCLI cli;

// Commands
Command cmdPing;
Command cmdMycommand;
Command cmdEcho;
Command cmdRm;
Command cmdLs;
Command cmdBoundless;
Command cmdSingle;
Command cmdHelp;

void setup() {
    Serial.begin(9600);
    Serial.println("Hello World!");

    cmdPing = cli.addCmd("ping");
    cmdPing.addArg("n", "10");

    cmdMycommand = cli.addCmd("mycommand");
    cmdMycommand.addArg("o");

    cmdEcho = cli.addCmd("echo");
    cmdEcho.addPosArg("text", "something");

    cmdRm = cli.addCmd("rm");
    cmdRm.addPosArg("file");

    cmdLs = cli.addCmd("ls");
    cmdLs.addFlagArg("a");

    cmdBoundless = cli.addBoundlessCmd("boundless");

    cmdSingle = cli.addSingleArgCmd("single");

    cmdHelp = cli.addCommand("help");

    Serial.println("Started!");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readString(); // Until('\n');

        if (input.length() > 0) {
            Serial.print("# ");
            Serial.println(input);

            cli.parse(input);
        }
    }

    if (cli.available()) {
        Command c = cli.getCmd();

        int argNum = c.countArgs();

        Serial.print("> ");
        Serial.print(c.getName());
        Serial.print(' ');

        for (int i = 0; i<argNum; ++i) {
            Argument arg = c.getArgument(i);
            // if(arg.isSet()) {
            Serial.print(arg.toString());
            Serial.print(' ');
            // }
        }

        Serial.println();

        if (c == cmdPing) {
            Serial.print(c.getArgument("n").getValue() + "x ");
            Serial.println("Pong!");
        } else if (c == cmdMycommand) {
            Serial.println("Hi " + c.getArgument("o").getValue());
        } else if (c == cmdEcho) {
            Argument str = c.getArgument(0);
            Serial.println(str.getValue());
        } else if (c == cmdRm) {
            Serial.println("Remove directory " + c.getArgument(0).getValue());
        } else if (c == cmdLs) {
            Argument a   = c.getArgument("a");
            bool     set = a.isSet();
            if (a.isSet()) {
                Serial.println("Listing directories");
            } else {
                Serial.println("Listing all directories");
            }
        } else if (c == cmdBoundless) {
            Serial.print("Boundless: ");

            for (int i = 0; i<argNum; ++i) {
                Argument arg = c.getArgument(i);
                if (i>0) Serial.print(",");
                Serial.print("\"");
                Serial.print(arg.getValue());
                Serial.print("\"");
            }
        } else if (c == cmdSingle) {
            Serial.println("Single \"" + c.getArg(0).getValue() + "\"");
        } else if (c == cmdHelp) {
            Serial.println("Help:");
            Serial.println(cli.toString());
        }
    }

    if (cli.errored()) {
        CommandError cmdError = cli.getError();

        Serial.print("ERROR: ");
        Serial.println(cmdError.toString());

        if (cmdError.hasCommand()) {
            Serial.print("Did you mean \"");
            Serial.print(cmdError.getCommand().toString());
            Serial.println("\"?");
        }
    }
}