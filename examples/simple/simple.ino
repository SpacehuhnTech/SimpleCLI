
// Include library
#include "Arduino_CLI.h"
using namespace arduino_cli;
Arduino_CLI* cli;

// some progmem strings used for the ping command
const char CLI_PING[] PROGMEM = "p,ping/s";
const char CLI_PONG[] PROGMEM = "pong!";
const char CLI_LINE[] PROGMEM = "l,line";
const char CLI_NUM[] PROGMEM = "n,number";
const char CLI_STR[] PROGMEM = "s,str/ing";

// #define Serial SERIAL_PORT_USBVIRTUAL // <- uncomment for SAMD21 (Arduino m0) boards!

void setup() {
    // start serial
    Serial.begin(115200);
    Serial.println();


    // =========== Create CommandParser =========== //
    cli = new Arduino_CLI();

    cli->onNotFound = [](String str) {
                          Serial.println("\"" + str + "\" not found");
                      };
    // ============================================ //


    // =========== Add hello command ========== //
    // hello world => hi from the world
    // hi toaster => hi from the toaster
    Command* hello = new Command("hello,hi", [](Cmd* cmd) {
        Serial.println("hi from the " +  cmd->value(0));
    });
    hello->addArg(new AnonymOptArg("world"));
    cli->addCommand(hello);
    // ======================================== //


    // =========== Add ping command =========== //
    // here using progmem strings to save RAM
    // ping => pong
    // ping -s ponk => ponk
    // ping -s ponk -n 2 => ponkponk
    // ping -s pink -n 2 -l => ponk
    //                         ponk
    Command_P* ping = new Command_P(CLI_PING, [](Cmd* cmd) { // CLI_PING = "p,ping/s";
        int h = cmd->value(CLI_NUM).toInt();                 // CLI_NUM = "n,number"

        if (cmd->isSet(CLI_LINE)) {                          // CLI_LINE = "l,line"
            for (int i = 0; i < h; i++) {
                Serial.println(cmd->value(CLI_STR));         // CLI_STR = "s,str/ing"
            }
        } else {
            for (int i = 0; i < h; i++) {
                Serial.print(cmd->value(CLI_STR)); // CLI_STR = "s,str/ing"
            }
            Serial.println();
        }
    });
    ping->addArg(new EmptyArg_P(CLI_LINE));         // CLI_LINE = "l,line"
    ping->addArg(new OptArg_P(CLI_STR, CLI_PONG));  // CLI_STR = "s,str/ing", CLI_PONG = "ping!"
    ping->addArg(new OptArg_P(CLI_NUM, PSTR("1"))); // CLI_NUM = "n,number"
    cli->addCommand(ping);
    // ======================================== //


    // run tests
    cli->parse("ping");
    cli->parse("ping -n 11");
    cli->parse("ping -n 11 -s test -l");
    cli->parse("hello world");
    cli->parse("hello toaster");


    Serial.println("\\o/ STARTED!");
}

void loop() {
    // read serial input
    if (Serial.available()) {
        String tmp = Serial.readStringUntil('\n');

        // print input
        if (tmp.length() > 0) {
            Serial.print("# ");
            Serial.println(tmp);
            // and parse it
            cli->parse(tmp);
        }
    }
}