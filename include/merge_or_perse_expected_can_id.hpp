#pragma once
#include <Arduino.h>

struct PersedExpectedCANID{  // 29bit
    uint16_t command;        // 13bit
    uint8_t  senderId;       // 8bit
    uint8_t  receiverId;     // 8bit
    bool     motorIsEnable[2]; // 2bit
};

PersedExpectedCANID perse_expected_can_id(uint32_t ID) {
    PersedExpectedCANID persed_id;
    
    persed_id.command        = ID >> 18;
    persed_id.senderId       = (ID >> 10) & 0xFF;
    persed_id.receiverId     = (ID >> 2 ) & 0xFF;
    persed_id.motorIsEnable[0] = ID & 0b10;
    persed_id.motorIsEnable[1] = ID & 0b01;
    
    return persed_id;
}

uint32_t merge_persed_expected_can_id(PersedExpectedCANID ID) {
    uint32_t merged_id {ID.command << 16 | ID.senderId << 8 | ID.receiverId << 2 | ID.motorIsEnable[0] << 1 | ID.motorIsEnable[1]}; 
    return merged_id;
}
