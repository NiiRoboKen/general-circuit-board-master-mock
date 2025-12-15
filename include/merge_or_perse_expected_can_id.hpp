#pragma once
#include <Arduino.h>

struct PersedExpectedCANID{  // 29bit
    uint16_t command;        // 13bit
    uint8_t  senderId;       // 8bit
    uint8_t  receiverId;     // 8bit
    bool     motorIsEnable[2]; // 2bit
    
    PersedExpectedCANID(uint16_t command, uint8_t sender_id, uint8_t receiver_id, bool motor_is_enable0, bool motor_is_enable1) :
        command(command),
        senderId(sender_id),
        receiverId(receiver_id),
        motorIsEnable({motor_is_enable0, motor_is_enable1}) {}
};

PersedExpectedCANID perse_expected_can_id(uint32_t ID) {
    return PersedExpectedCANID(
        ID >> 18,
        (ID >> 10) & 0xFF,
        (ID >> 2 ) & 0xFF,
        ID & 0b10,
        ID & 0b01
    );    
}

uint32_t merge_persed_expected_can_id(PersedExpectedCANID ID) {
    uint32_t merged_id {ID.command << 16 | ID.senderId << 8 | ID.receiverId << 2 | ID.motorIsEnable[0] << 1 | ID.motorIsEnable[1]}; 
    return merged_id;
}
