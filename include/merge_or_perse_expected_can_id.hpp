#pragma once
#include <Arduino.h>

struct PersedExpectedCANID{ // 29bit
    uint16_t command;       // 13bit
    uint8_t  senderId;      // 8bit
    uint8_t  receiverId;    // 8bit
};

PersedExpectedCANID perse_expected_can_id(uint32_t ID) {
    PersedExpectedCANID persed_id;
    
    persed_id.command    = ID >> 16;
    persed_id.senderId   = (ID >> 8) & 0xFF;
    persed_id.receiverId = ID & 0xFF;
    
    return persed_id;
}

uint32_t merge_persed_expected_can_id(PersedExpectedCANID ID) {
    uint32_t merged_id;
    
    merged_id = ID.command << 8;
    merged_id = merged_id | ID.senderId;
    merged_id = merged_id << 8 | ID.receiverId;
    
    return merged_id;
}
