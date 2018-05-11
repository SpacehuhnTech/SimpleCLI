#include "Arduino_CLI.h"

using namespace arduino_cli;

Arduino_CLI* cli;

const char CLI_PING[] PROGMEM = "p,ping/s";
const char CLI_PONG[] PROGMEM = "pong!";
const char CLI_LINE[] PROGMEM = "l,line";
const char CLI_NUM[] PROGMEM = "n,number";
const char CLI_STR[] PROGMEM = "s,str/ing";

// #define Serial SERIAL_PORT_USBVIRTUAL // for the SAMD21 chips

void setup() {
    Serial.begin(115200);
    Serial.println();

    // =========== Create CommandParser =========== //
    cli = new Arduino_CLI();

    cli->onNotFound = [](String str) {
                          Serial.println("\"" + str + "\" not found");
                      };
    // ============================================ //

    // =========== Add hello command ========== //
    Command* hello = new Command("hello", [](Cmd* cmd) {
        String from = cmd->value(0);

        if (from.length() > 0) Serial.println("hi from the " + from);
        else Serial.println("hi");
    });
    hello->addArg(new AnonymOptArg(""));
    cli->addCommand(hello);
    // ======================================== //

    // =========== Add ping command =========== //
    // here using progmem strings to save RAM
    Command_P* ping = new Command_P(CLI_PING, [](Cmd* cmd) {
        int h = cmd->value(CLI_NUM).toInt();

        if (cmd->isSet(CLI_LINE)) {
            for (int i = 0; i < h; i++) {
                Serial.println(cmd->value(CLI_STR));
            }
        } else {
            for (int i = 0; i < h; i++) {
                Serial.print(cmd->value(CLI_STR));
            }
            Serial.println();
        }
    });
    ping->addArg(new EmptyArg_P(CLI_LINE));
    ping->addArg(new OptArg_P(CLI_STR, CLI_PONG));
    ping->addArg(new OptArg_P(CLI_NUM, PSTR("1")));
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
    if (Serial.available()) {
        String tmp = Serial.readStringUntil('\n');

        if (tmp.length() > 0) {
            Serial.print("# ");
            Serial.println(tmp);
            cli->parse(tmp);
        }
    }
}