#pragma once
#include <Arduino.h>

struct PersedExpectedCANID{ // 29bit
    uint16_t command;       // 13bit
    uint8_t  senderId;      // 8bit
    uint8_t  receiverId;    // 8bit
};

PersedExpectedCANID perse_expected_can_id(uint32_t ID) {
    PersedExpectedCANID PersedID;
    
    PersedID.command    = ID >> 16;
    PersedID.senderId   = (ID >> 8) & 0xFF;
    PersedID.receiverId = ID & 0xFF;
}
