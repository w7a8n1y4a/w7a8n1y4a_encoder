#include "w7a8n1y4a_encoder.h"
#include <Arduino.h>

const int8_t KNOBDIR[] = {
  0, -1,  1,  0,
  1,  0,  0, -1,
  -1,  0,  0,  1,
0,  1, -1,  0  };
w7a8n1y4a_encoder::w7a8n1y4a_encoder(uint8_t clk, uint8_t dt, int8_t sw) {
    _CLK = clk;
	  _DT = dt;
    _SW = sw;
	
	pinMode(_CLK, INPUT);
	pinMode(_DT, INPUT);	
	pinMode(_SW, INPUT);	

	old_state = 0x3;
	position = 0;
  exit_position = 0;
  old_exit_position = 0;

}

void w7a8n1y4a_encoder::tick(){
  millis_timer = millis();
  int8_t sw_state = digitalRead(_SW);

  int8_t state = digitalRead(_CLK) | (digitalRead(_DT) << 1);
  //обработка вариации работы энкодера
  if (old_state != state) {
    encoder_state = 0;
    position += KNOBDIR[state | (old_state << 2)];
    if (state == 0x3 && position != 0) {
				encoder_state = (position == 4) ? 1 : 2;
				position = 0;
		}
    old_state = state;
  }
  if(encoder_state != 0){
    if(sw_state == 0){
      encoder_state += 4;
      if(millis_timer-fast_timer < timeout_fast_turn){
        encoder_state += 2;
        fast_timer = millis_timer;
      }else{
        fast_timer = millis_timer;
      }
    }else{
      if(millis_timer-fast_timer < timeout_fast_turn){
        encoder_state += 2;
        fast_timer = millis_timer;
      }else{
        fast_timer = millis_timer;
      }
    }
  }
  //обработка кнопок
  if(!sw_state && !button_flag && millis_timer - button_timer > timeout_debounce_click){
      button_state = 1;
      button_flag = 1;
      button_long_flag = 0;
      button_timer = millis_timer;
      button_allow_double_flag = 1;
  }
  if(sw_state && button_flag && millis_timer - button_timer > timeout_debounce_click){
    if(button_long_flag_double){
      button_long_flag_double = 0;
    }else{
      button_state = 2;
    }
      button_flag = 0;
    button_timer = millis_timer;
    if(button_allow_double_flag && !button_double_flag ){
      button_double_flag = 1;
      button_count_flag = 0;
    }else{
      button_count_flag = 1;
    }
  }
  if(button_double_flag && millis_timer - button_timer > timeout_double_click){
    if(button_count_flag){
      button_state = 3;
    }
    button_double_flag = 0;
  }
  if(button_flag && millis_timer - button_timer > timeout_long_click && !button_long_flag){
    if(!sw_state){
      button_state = 4;
      button_long_flag = 1;
      button_flag = 1;
      button_long_flag_double = 1;
    }
  }
}

bool w7a8n1y4a_encoder::left(){
  if(encoder_state == 1){
    encoder_state = 0;
    return 1;
  }else{
    return 0;
  }
}
bool w7a8n1y4a_encoder::right(){
  if(encoder_state == 2){
    encoder_state = 0;
    return 1;
  }else{
    return 0;
  }
}
bool w7a8n1y4a_encoder::press_left(){
  if(encoder_state == 5){
    encoder_state = 0;
    return 1;
  }else{
    return 0;
  }
}
bool w7a8n1y4a_encoder::press_right(){
  if(encoder_state == 6){
    encoder_state = 0;
    return 1;
  }else{
    return 0;
  }
}

bool w7a8n1y4a_encoder::fast_left(){
  if(encoder_state == 3){
    encoder_state = 0;
    return 1;
  }else{
    return 0;
  }
}
bool w7a8n1y4a_encoder::fast_right(){
  if(encoder_state == 4){
    encoder_state = 0;
    return 1;
  }else{
    return 0;
  }
}
bool w7a8n1y4a_encoder::fast_press_left(){
  if(encoder_state == 7){
    encoder_state = 0;
    return 1;
  }else{
    return 0;
  }
}
bool w7a8n1y4a_encoder::fast_press_right(){
  if(encoder_state == 8){
    encoder_state = 0;
    return 1;
  }else{
    return 0;
  }
}

bool w7a8n1y4a_encoder::press(){
  if(button_state == 2){
    button_state = 0;
    return 1;
  }else{
    return 0;
  }
}

bool w7a8n1y4a_encoder::long_press(){
  if(button_state == 4){
    button_state = 0;
    return 1;
  }else{
    return 0;
  }
}
bool w7a8n1y4a_encoder::double_press(){
  if(button_state == 3){
    button_state = 0;
    return 1;
  }else{
    return 0;
  }
}
