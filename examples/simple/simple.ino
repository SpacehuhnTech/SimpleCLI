
// Include library
#include "Arduino_CLI.h"
using namespace arduino_cli;
Arduino_CLI* cli;

// #define Serial SERIAL_PORT_USBVIRTUAL // <- uncomment for SAMD21 (Arduino m0) boards!

void setup() {
    // start serial
    Serial.begin(115200);
    Serial.println();


    // =========== Create CommandParser =========== //
    cli = new Arduino_CLI();

    // when no valid command could be found for given user input
    cli->onNotFound = [](String str) {
                          Serial.println("\"" + str + "\" not found");
                      };
    // ============================================ //


    // =========== Add hello command ========== //
    // hello => world says hello :)
    // hello toaster => toaster says hello :)
    Command* hello = new Command("hello", [](Cmd* cmd) {
        Serial.println(cmd->getValue(0) + " says hello :)");
    });
    hello->addArg(new AnonymOptArg("world"));
    cli->addCmd(hello);
    // ======================================== //


    // =========== Add ping command =========== //
    // ping                 => pong
    // ping -s ponk         => ponk
    // ping -s ponk -n 2    => ponkponk
    // ping -s ponk -n 2 -l => ponk
    //                         ponk
    Command* ping = new Command("ping", [](Cmd* cmd) {
        int h = cmd->getValue("n").toInt();

        if (cmd->isSet("l")) { // with linebreak
            for (int i = 0; i < h; i++) Serial.println(cmd->getValue("s"));
        } else {
            for (int i = 0; i < h; i++) Serial.print(cmd->getValue("s"));
            Serial.println();
        }
    });
    ping->addArg(new EmptyArg("l"));
    ping->addArg(new OptArg("s", "ping!"));
    ping->addArg(new OptArg("n", "1"));
    cli->addCmd(ping);
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

        if (tmp.length() > 0) {
            // print input
            Serial.print("# ");
            Serial.println(tmp);
            // and parse it
            cli->parse(tmp);
        }
    }
}