/*
   ---------------------------------------------------------
   Mini Deck

   Copyright (c) 2021 Uwe B. Meding -- All Rights Reserved.
   ---------------------------------------------------------
*/

#include "Configuration.h"

int second = 0;
int checkReset2nd() {
  int current = second;
  if (second) {
    second  = second ^ 1;
    rxOff();
  }
  return current;
}
int noret = 0;
int checkNoRet() {
  return noret;
}



void onKey1() {
  txOn();
  if (checkReset2nd()) {
    Keyboard.print(NPASSWORD);
  } else {
    Keyboard.print(PASSWORD);
  }
  if (!checkNoRet()) {
    Keyboard.press(KEY_RETURN);
  }
  Keyboard.releaseAll();
  delay(100);
  txOff();
}
void onKey2() {
  txOn();
  if (checkReset2nd()) {
    noret = noret ^ 1;
  } else {
    Keyboard.print(USERNAME);
    Keyboard.press(KEY_TAB);
  }
  Keyboard.releaseAll();
  delay(200);
  txOff();
}
void onKey3() {
  txOn();

  //  Keyboard.press(KEY_LEFT_ALT);
  //  Keyboard.press(KEY_LEFT_CTRL);
  //  Keyboard.press(KEY_DELETE);
  //  Keyboard.releaseAll();

  // Wiggle the mouse and click to wake up
  for (int i = 0; i < 5; i++) {
    delay(30);
    Mouse.move(100, 0);
    delay(30);
    Mouse.move(-100, 0);
  }
  Mouse.click();


  delay(100);
  txOff();
}
void onKey4() {
  txOn();
  if (checkReset2nd()) {
    // MS teams: video on/off
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_GUI);     // Mac
    //Keyboard.press(KEY_LEFT_CTRL);  // Windoze
    Keyboard.print("O");
  } else {
    // MS teams: mute on/off
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_GUI);     // Mac
    //Keyboard.press(KEY_LEFT_CTRL);  // Windoze
    Keyboard.print("M");
  }
  Keyboard.releaseAll();
  delay(200);
  txOff();
}


char *greeting[] = {
  "best,",
  "Thanks,",
  "Thanks",
  "regards,",
  "Tx,",
  "thx,"
};

void onKey5() {
  txOn();
  if (checkReset2nd()) {
    int pos = random(0, sizeof(greeting) / sizeof(char*));
    char *msg = greeting[pos];
    Keyboard.print(msg);
    Keyboard.press(KEY_RETURN);
  } else {
    Keyboard.print("Let me know if you have any questions,\n\n");
    Keyboard.print("Thanks,");
  }
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.print("Uwe");
  Keyboard.releaseAll();

  delay(100);

  txOff();
}

void onKey6() {
  second = second ^ 1;
  if (second) {
    rxOn();
  } else {
    rxOff();
  }
  delay(200);
}
