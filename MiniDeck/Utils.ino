

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
