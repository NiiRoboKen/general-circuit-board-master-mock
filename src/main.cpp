#include <Arduino.h>
#include <esp_can.hpp>

#include "mock_config.hpp"
#include "merge_or_perse_expected_can_id.hpp"

CanDriver can;
ExcutableCommandState current_state{configring};

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
    PersedExpectedCANID persed_msg_id = perse_expected_can_id(msg.identifier);
    if(persed_msg_id.receiverId != BOARD_ID) {
        Serial.println("invaild CAN ID: unequal receiver ID");
        return;
    }
    
    if(current_state.canExcute(persed_msg_id.command)) {
        switch(persed_msg_id.command) {
            case 0x0000 :
                Serial.println("STOP: board stop by reboot.");
                while(1) delay(100);
                break;
            case 0x0001 :
                Serial.println("RESET: board reboot. WARN: esp_restart() reset only CPU without peripherals.");
                esp_restart();
                break;
            case 0x0002 :
                PersedExpectedCANID pong(
                    0x0003,
                    BOARD_ID,
                    0xFFFF,
                    0,0
                );
                uint8_t empty_data[] = {0};

                can.sendExtended(merge_persed_expected_can_id(pong), empty_data, 1);
                Serial.println("PING: return PONG.");
                break;
            case 0x0010 :
                Serial.println("SET CONFIG: ");
                break;
            case 0x0011 :
                Serial.println("SET PID GAIN (ANGLE): ");
                break;
            case 0x0012 :
                Serial.println("SET PID GAIN (RPM): ");
                break;
            case 0x0101 :
                Serial.println("SET ANGLE: ");
                break;
            case 0x0102 :
                Serial.println("SET RPM: ");
                break;
            case 0x0103 :
                Serial.println("SET DUTY: ");
                break;
            case 0x0111 :
                Serial.println("REQUEST GET ANGLE: ");
                break;
            case 0x0112 :
                Serial.println("REQUEST GET RPM: ");
                break;

            default:
                Serial.print("command not found: ");
                Serial.println(persed_msg_id.command);
                break;
        }
    } else {
        return;
    }
}
