/*
   Utilities
*/
#include "Configuration.h"


// ==========================================================
// Setup the mini deck
//
void setup() {
  Keyboard.begin();

  // get some random analog noise as seed
  randomSeed(analogRead(0));
  
  ledInit();

  pinMode(KILL_SWITCH_PIN, INPUT);

  pinMode(MDK1, INPUT);
  pinMode(MDK2, INPUT);
  pinMode(MDK3, INPUT);
  pinMode(MDK4, INPUT);
  pinMode(MDK5, INPUT);
  pinMode(MDK6, INPUT);
}

// ==========================================================
// Loop + modes
//
#define NORMAL 1
#define KEY_ID 2

#define RUNMODE NORMAL
/*
   Wait for a key to get pressed, then handle it.
*/
void loop()
{
  if (digitalRead(KILL_SWITCH_PIN) == HIGH) {

#if RUNMODE == NORMAL
    if (digitalRead(MDK1) == HIGH) onKey1();
    if (digitalRead(MDK2) == HIGH) onKey2();
    if (digitalRead(MDK3) == HIGH) onKey3();
    if (digitalRead(MDK4) == HIGH) onKey4();
    if (digitalRead(MDK5) == HIGH) onKey5();
    if (digitalRead(MDK6) == HIGH) onKey6();
#endif

#if RUNMODE == KEY_ID
    // identify keys
    if (digitalRead(MDKx) == HIGH)
      syncBlink();
#endif

  } else {

    // The kill switch has been triggered. We are in the
    // safety mode -- just blink
    alternateBlink();
  }
}

// --- LED helpers
void ledInit() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RXLED, OUTPUT);
  pinMode(TXLED, OUTPUT);
  ledOff();
}
void ledOff() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(RXLED, HIGH);
  digitalWrite(TXLED, HIGH);
}
void ledOn() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(RXLED, LOW);
  digitalWrite(TXLED, LOW);
}
void txOn() {
  digitalWrite(TXLED, LOW);
}
void txOff() {
  digitalWrite(TXLED, HIGH);
}
void rxOn() {
  digitalWrite(RXLED, LOW);
}
void rxOff() {
  digitalWrite(RXLED, HIGH);
}

int BLINK_STATE = 0;
/*
   Blink the RX/TX LED's alternately
*/
void alternateBlink() {
  if (BLINK_STATE) {
    digitalWrite(RXLED, LOW);
    digitalWrite(TXLED, HIGH);
  } else {
    digitalWrite(RXLED, HIGH);
    digitalWrite(TXLED, LOW);
  }
  BLINK_STATE = !BLINK_STATE;
  delay(100);
}

/*
   Blink the RX/TX LED's together
*/
void syncBlink() {
  if (BLINK_STATE) {
    digitalWrite(RXLED, HIGH);
    digitalWrite(TXLED, HIGH);
  } else {
    digitalWrite(RXLED, LOW);
    digitalWrite(TXLED, LOW);
  }
  BLINK_STATE = !BLINK_STATE;
  delay(100);
}
