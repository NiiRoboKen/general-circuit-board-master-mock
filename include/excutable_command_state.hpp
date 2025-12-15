#pragma once

#include <Arduino.h>

class ExcutableCommandState{
    public:
    ExcutableCommandState(uint16_t* command, int commands_sum);
    
    bool canExcute(uint16_t command);
    
    private:
    const uint16_t* m_excutable_commands;
    const uint16_t  m_core_commands[3] = {0x0000, 0x0001, 0x0002};
    const int       m_excutable_commands_sum;
};

ExcutableCommandState::ExcutableCommandState(uint16_t* commands, int commands_sum) :
    m_excutable_commands(commands),
    m_excutable_commands_sum(commands_sum) {
    commands[commands_sum];
}

bool ExcutableCommandState::canExcute(uint16_t command) {
    for(uint16_t core_command : m_core_commands)
        if(command == core_command) return true;
    for(int i = 0; i < m_excutable_commands_sum; i++)
        if(command == m_excutable_commands[i]) return true;
    return false;
}
