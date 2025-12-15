#pragma once

// board config
#define BOARD_ID 0x1

// serial config
#define SERIAL_BAUDRATE 9600

// CAN config
#define CAN_BAUDRATE 1000E3
#define CAN_TX_PIN   4
#define CAN_RX_PIN   5

// state config
#include "excutable_command_state.hpp"
namespace {
    uint16_t config_commands[1] = {
        0x0010
    };
    uint16_t config_angle_pid_commands[1] = {
        0x0011
    };
    uint16_t config_speed_pid_commands[1] = {
        0x0012
    };
    uint16_t run_angle_pid_commands[2] = {
        0x0101,
        0x0111
    };
    uint16_t run_speed_pid_commands[2] = {
        0x0102,
        0x0112
    };
    uint16_t run_duty_commands[1] = {
        0x0103
    };
}
ExcutableCommandState configring            = ExcutableCommandState(config_commands, 1);
ExcutableCommandState configring_angle_pid  = ExcutableCommandState(config_angle_pid_commands, 1);
ExcutableCommandState configring_speed_pid  = ExcutableCommandState(config_speed_pid_commands, 1);
ExcutableCommandState running_angle_pid     = ExcutableCommandState(run_angle_pid_commands, 2);
ExcutableCommandState running_speed_pid     = ExcutableCommandState(run_speed_pid_commands, 2);
ExcutableCommandState running_duty          = ExcutableCommandState(run_duty_commands, 1);
