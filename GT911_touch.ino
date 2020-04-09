#include <Wire.h>
#include "Goodix.h"

#define INT_PIN 23
#define RST_PIN -1 // -1 if pin is connected to VCC else set pin number


Goodix touch = Goodix();

void handleTouch(int8_t contacts, GTPoint *points) {
  log_printf("Contacts: %d\n", contacts);
  for (uint8_t i = 0; i < contacts; i++) {
    log_printf("C%d: #%d %d,%d s:%d\n", i, points[i].trackId, points[i].x, points[i].y, points[i].area);
    yield();
  }
}

void touchStart() {
 if (touch.begin(INT_PIN, RST_PIN)!=true) {
    Serial.println("! Module reset failed");
  } else {
    Serial.println("Module reset OK");
  }
  
  Serial.print("Check ACK on addr request on 0x");
  Serial.print(touch.i2cAddr, HEX);
  
  Wire.beginTransmission(touch.i2cAddr);  
  int error = Wire.endTransmission();
  if (error == 0) {    
    Serial.println(": SUCCESS");   
  } else {
    Serial.print(": ERROR #");
    Serial.println(error);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nGoodix GT911x touch driver");

  Wire.setClock(400000);
  Wire.begin();
  delay(300);

  touch.setHandler(handleTouch);
  touchStart();
}

void loop() {  
  touch.loop();
  delay(1);
}
