#define CLK D5
#define DT D6
#define SW D7

#include <w7a8n1y4a_encoder.h>

w7a8n1y4a_encoder w7a8n1y4a(CLK, DT, SW);

void setup() {
  Serial.begin(115200);
}
void loop() {
  w7a8n1y4a.tick();


  if(w7a8n1y4a.left()){
    Serial.println("left");
  } 
  if(w7a8n1y4a.right()){
    Serial.println("right");
  }
  if(w7a8n1y4a.press_left()){
    Serial.println("press_left");
  }
  if(w7a8n1y4a.press_right()){
    Serial.println("press_right");
  }

  if(w7a8n1y4a.fast_left()){
    Serial.println("fast_left");
  } 
  if(w7a8n1y4a.fast_right()){
    Serial.println("fast_right");
  }
  if(w7a8n1y4a.fast_press_left()){
    Serial.println("fast_press_left");
  }
  if(w7a8n1y4a.fast_press_right()){
    Serial.println("fast_press_right");
  }

  if(w7a8n1y4a.press()){
    Serial.println("press");
  } 
  if(w7a8n1y4a.long_press()){
    Serial.println("long_press");
  }
  if(w7a8n1y4a.double_press()){
    Serial.println("double_press");
  }
}
