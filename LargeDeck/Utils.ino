/*
   Utilities
*/
#include "Configuration.h"


// ---------------------------------------
// Keyboard matrix
// Row pins: top -> down
static const uint8_t rowPins[] = { 8, 9, 16 };
static const uint8_t nRows = sizeof(rowPins) / sizeof(uint8_t);

// Col pins: left -> right
static const uint8_t colPins[] = { 7, 6, 5, 4, 3, 2};
static const uint8_t nCols = sizeof(colPins) / sizeof(uint8_t);

// Debounce counter, one per switch
static int8_t debounceCounter[nRows][nCols];
// Debounce sense
#define DEBOUNCE_SENSE 3

// Current row for the keyboard scanner. We use the loop() to
// advance/reset the counter.
static int8_t currentScanRow;

// Key callbacks, each key has a callback holder
// to a 'void func()'
struct Callback {
  int delay;
  int indicator;
  void (*func)();

};
static struct Callback keyCallbacks[nRows][nCols];
//static void (* keyCallbacks[nRows][nCols])();


// ==========================================================
// Setup the large deck
//
void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  // initialize key bindings
  initializeCallbacks();
  initializeKeyBindings();

  // get some random analog noise as seed
  randomSeed(analogRead(0));

  ledInit();

  // setup kill switch
  pinMode(KILL_SWITCH_PIN, INPUT);
  digitalWrite(KILL_SWITCH_PIN, HIGH);

  // external block
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  
  setupSwitchPins();
  // initialize the debounce counters
  for (uint8_t i = 0; i < nRows; i++) {
    for (uint8_t j = 0; j < nCols; j++) {
      debounceCounter[i][j] = 0;
    }
  }

  // initialize the keyboard row scanner
  currentScanRow = -1;
}

// ==========================================================
// Loop + modes
//

/*
   Wait for a key to get pressed, then handle it.
*/
void loop()
{
  // Note: the logic of the kill switch pin is different
  //       than the MiniDeck!
  if (digitalRead(KILL_SWITCH_PIN) == LOW) {

    scanKeyboard();

  } else {

    // The kill switch has been triggered. We are in the
    // safety mode -- just blink
    alternateBlink();
  }
}


static void scanKeyboard() {

  // loop counters
  uint8_t i, j;

  // calculate the next keyboard row to scan
  currentScanRow = (++currentScanRow % nRows);

  digitalWrite(rowPins[currentScanRow], LOW);

  // go through the keys on the current scan row
  for (i = 0; i < nCols; i++) {
    if (digitalRead(colPins[i]) == LOW) {
      debounceCounter[currentScanRow][i]++;
      if (debounceCounter[currentScanRow][i] > DEBOUNCE_SENSE) {
        // key pressed
        /*
          Serial.print("key ");
          Serial.print(currentScanRow);
          Serial.print(" ");
          Serial.print(i);
          Serial.println();
        */
        invokeCallback(currentScanRow, i);
      }
    } else {
      debounceCounter[currentScanRow][i]--;
      if (debounceCounter[currentScanRow][i] == 0) {
        // key released
      }
    }
  }

  digitalWrite(rowPins[currentScanRow], HIGH);
}

// -- Helper
static void setupSwitchPins() {

  // button drive row: active LOW
  for (uint8_t i = 0; i < nRows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  // button select columns: pull up, will be active on LOW
  for (uint8_t i = 0; i < nCols; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

// ==========================================================
// Callback handling
void initializeCallbacks() {
  for (int i = 0; i < nRows; i++) {
    for (int j = 0; j < nCols; j++) {
      keyCallbacks[i][j] = {
        .delay = 0,
        .indicator = 0,
        .func = NULL
      };
    }
  }
}
// Setup callback for the keys by row/col, ignore bad values
void onNormalKeyPress(int row, int col, void (*func)()) {
  onRawKeyPress(row, col, 200, 1, func);
}
void onRawKeyPress(int row, int col, int delay, int indicator, void (*func)()) {
  if (row < 0 || row >= nRows || col < 0 || col >= nCols)
    return;
  keyCallbacks[row][col] = {
    .delay = delay,
    .indicator = indicator,
    .func = func
  };
}

// invoke a callback
void invokeCallback(int row, int col) {
  struct Callback cb = keyCallbacks[row][col];
  if (cb.func != NULL) {
    if (cb.indicator) {
      txOn();
    }

    (*cb.func)();
    if (cb.delay > 0) {
      delay(cb.delay);
    }

    if (cb.indicator) {
      txOff();
    }
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
