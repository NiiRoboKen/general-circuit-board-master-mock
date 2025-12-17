#pragma once

#include "excutable_command_state.hpp"

class CurrentState{
    public:
    CurrentState(ExcutableCommandState* init_state);
    
    bool canExcute(uint16_t command);
    void update(ExcutableCommandState* next_state);

    private:
    ExcutableCommandState* m_current_state;
};

CurrentState::CurrentState(ExcutableCommandState* init_state) :
    m_current_state(init_state) {}
    
bool CurrentState::canExcute(uint16_t command) { return m_current_state->canExcute(command); }
void CurrentState::update(ExcutableCommandState* next_state) { m_current_state = next_state; }
