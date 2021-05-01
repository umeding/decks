/*
   ---------------------------------------------------------
   Mini Deck

   Copyright (c) 2021 Uwe B. Meding -- All Rights Reserved.
   ---------------------------------------------------------
*/

#include "Configuration.h"

void setup() {
  Keyboard.begin();

  ledInit();

  pinMode(KILL_SWITCH_PIN, INPUT);

}
/*
   Wait for a key to get pressed, then handle it.
*/
void loop()
{
  if (digitalRead(KILL_SWITCH_PIN) == HIGH) {
    //handleKeyStrokes();

    if(digitalRead(MDKx) == HIGH)
        syncBlink();

  } else {
    
    // The kill switch has been triggered. We are in the
    // safety mode -- just blink
    alternateBlink();
  }
}
