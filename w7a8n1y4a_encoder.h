#pragma once
#include <Arduino.h>

class w7a8n1y4a_encoder{
public:

    w7a8n1y4a_encoder(uint8_t clk, uint8_t dt, int8_t sw);

    void tick();

    bool left();
    bool right();
    bool press_left();
    bool press_right();

    bool fast_left();
    bool fast_right();
    bool fast_press_left();
    bool fast_press_right();

    bool press();
    bool long_press();
    bool double_press();

private:
    uint8_t _CLK = 0, _DT = 0, _SW = 0;

    uint8_t timeout_long_click = 500;
    uint8_t timeout_double_click = 200;
    uint8_t timeout_debounce_click = 50;
    uint8_t timeout_fast_turn = 30;

    uint8_t encoder_state = 0;
    uint8_t button_state = 0;

    uint32_t millis_timer = 0;
    uint32_t fast_timer = 0;
    uint32_t button_timer = 0;

    bool button_flag = 0;
    bool button_count_flag = 0;
    bool button_double_flag = 0;
    bool button_allow_double_flag = 0;
    bool button_long_flag = 0;
    bool button_long_flag_double = 0;



    volatile int8_t old_state;
    volatile long position;
    volatile long exit_position;
    volatile long old_exit_position;

};
