
// Include library
#include "SimpleCLI.h"
using namespace simplecli;

// create an instance of it
SimpleCLI* cli;

// #define Serial SERIAL_PORT_USBVIRTUAL // <- uncomment for SAMD21 (Arduino m0) boards!

void setup() {
    // start serial
    Serial.begin(115200);
    Serial.println();


    // =========== Create CommandParser =========== //
    cli = new SimpleCLI();

    // when no valid command could be found for given user input
    cli->onNotFound = [](String str) {
                          Serial.println("\"" + str + "\" not found");
                      };
    // ============================================ //


    // =========== Add hello command ========== //
    // hello => hello world!
    cli->addCmd(new Command("hello", [](Cmd* cmd) {
        Serial.println("hello world");
    }));
    // ======================================== //


    // =========== Add ping command =========== //
    // ping                 => pong
    // ping -s ponk         => ponk
    // ping -s ponk -n 2    => ponkponk
    Command* ping = new Command("ping", [](Cmd* cmd) {
        int h = cmd->getValue("n").toInt();

        for (int i = 0; i < h; i++) {
            Serial.print(cmd->getValue("s"));
        }
    });
    ping->addArg(new OptArg("s", "ping!"));
    ping->addArg(new OptArg("n", "1"));
    cli->addCmd(ping);
    // ======================================== //


    // run tests
    cli->parse("ping");
    cli->parse("hello");

    Serial.println("Started!");
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