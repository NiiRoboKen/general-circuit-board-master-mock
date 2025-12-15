#include <Arduino.h>
#include <esp_can.hpp>

#include "mock_config.hpp"
#include "perse_expected_can_id.hpp"

CanDriver can;

void can_callback(twai_message_t msg);

void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("general-circuit-board-slave-mock");

    if(can.begin(CAN_BAUDRATE, CAN_TX_PIN, CAN_RX_PIN)) Serial.println("CAN initialized successfully.");
    else                                                Serial.println("CAN initialize failed.");
    can.onReceive(can_callback);
}

void loop() {

}

void can_callback(twai_message_t msg) {
    Serial.print("Received: ");

    if(!msg.flags) {
        Serial.println("invaild CAN ID: Standard ID");
        return;
    }
    if(perse_expected_can_id(msg.identifier).receiverId != BOARD_ID) {
        Serial.println("invaild CAN ID: unequal receiver ID");
        return;
    }
}
