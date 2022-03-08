/*
   ---------------------------------------------------------
   Large Deck

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

// called from setup()
void initializeKeyBindings() {
  onNormalKeyPress(0, 0, sendLeft);
  onNormalKeyPress(0, 2, sendRight);
  onNormalKeyPress(0, 1, maximize);
  onNormalKeyPress(1, 0, snapLeft);
  onNormalKeyPress(1, 2, snapRight);


  onRawKeyPress(0, 5, 0, 0, enterSecondMode);
  onNormalKeyPress(2, 5, sendEmailGreeting);
  onNormalKeyPress(2, 3, newTab);
  //  onNormalKeyPress(2, 2, becomeRoot);
  //onNormalKeyPress(0, 2, awsLogin);

  onNormalKeyPress(0, 3, sendPassword);
  onNormalKeyPress(0, 4, areaScreenShot);

  // copy -> find -> paste
  onNormalKeyPress(1, 3, kbCopy);
  onNormalKeyPress(1, 4, kbFind);
  onNormalKeyPress(1, 5, kbPaste);

  // --- scrolling
  onRawKeyPress(1, 1, 50, 1, scrollUp);
  onRawKeyPress(2, 1, 50, 1, scrollDown);
  onRawKeyPress(2, 0, 50, 1, scrollLeft);
  onRawKeyPress(2, 2, 50, 1, scrollRight);
}

void kbCopy() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.print("c");
  Keyboard.releaseAll();
}

void kbFind() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.print("f");
  Keyboard.releaseAll();
}

void kbPaste() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.print("v");
  Keyboard.releaseAll();
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}

void sendLeft() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.releaseAll();
}
void sendRight() {
  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(KEY_RIGHT_GUI);
  Keyboard.press(KEY_RIGHT_ARROW);
  Keyboard.releaseAll();
}
void maximize() {
  if (checkReset2nd()) {
    Keyboard.press(KEY_RIGHT_GUI);
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.releaseAll();
  } else {
    Keyboard.press(KEY_RIGHT_GUI);
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.releaseAll();
  }
}
void snapLeft() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.releaseAll();
}
void snapRight() {
  Keyboard.press(KEY_RIGHT_GUI);
  Keyboard.press(KEY_RIGHT_ARROW);
  Keyboard.releaseAll();
}
void sendPassword() {
  if (checkReset2nd()) {
    Keyboard.print(NPASSWORD);
  } else {
    Keyboard.print(PASSWORD);
  }
  if (!checkNoRet()) {
    Keyboard.press(KEY_RETURN);
  }
  Keyboard.releaseAll();
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
// ==================================================
int fan = 0;
void fanMode() {
  fan  = fan ^ 1;
  digitalWrite(14, fan ? HIGH : LOW);
}
// ==================================================
void becomeRoot() {
  if (checkReset2nd()) {

  } else {
    Keyboard.print("su -");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(50);
    Keyboard.print("ccaes1");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
  }
}
// ==================================================
void newTab() {
  if (checkReset2nd()) {

  } else {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.print("t");
  }
  Keyboard.releaseAll();
}
// ==================================================
#define KEY_PRNT_SCRN 0xCE
void areaScreenShot() {
  if (checkReset2nd()) {
    Keyboard.print("xclip -selection c -t image/png -o > .png");
    for (int i = 0; i < 4; i++) {
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.releaseAll();
    }
  } else {
    // reply to all
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_PRNT_SCRN);
    Keyboard.releaseAll();
  }
}

// ==================================================
char *shortGreeting[] = {
  //"best,",
  "Thanks,",
  "thanks",
  "regards,",
  "Tx,",
  "thx,"
};
char *longGreeting[] = {
  "Let me know if you have any questions,",
  "Any questions, let me know.",
  "Any questions/comments, let me know."
};

void sendEmailGreeting() {
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  if (checkReset2nd()) {
    int pos = random(0, sizeof(longGreeting) / sizeof(char*));
    char *msg = longGreeting[pos];
    Keyboard.print(msg);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    Keyboard.print("Thanks,");
  } else {
    int pos = random(0, sizeof(shortGreeting) / sizeof(char*));
    char *msg = shortGreeting[pos];
    Keyboard.print(msg);
  }
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.print("Uwe");
  Keyboard.releaseAll();
}


void awsLogin() {
  if (checkReset2nd()) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("n");
    Keyboard.releaseAll();
    delay(5000);
    __awsControlTower();
  } else {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.print("t");
    Keyboard.releaseAll();
    delay(500);
    __awsControlTower();
    __awsLoginSequence();
  }
}
void __awsControlTower() {
  Keyboard.print("https://d-906702d918.awsapps.com/start/#/");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(10000);
}
void __awsLoginSequence() {
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  Keyboard.print(EMAIL);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(1000);

  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  Keyboard.print(PASSWORD);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

}


void enterSecondMode() {
  second = second ^ 1;
  if (second) {
    rxOn();
  } else {
    rxOff();
  }
  delay(200);
}

#define WHEEL_INCREMENT 5
void scrollUp() {
  Mouse.move(0, 0, WHEEL_INCREMENT);
}

void scrollDown() {
  Mouse.move(0, 0, -WHEEL_INCREMENT);
}

void scrollLeft() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Mouse.move(0, 0, WHEEL_INCREMENT);
  Keyboard.releaseAll();
}

void scrollRight() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Mouse.move(0, 0, -WHEEL_INCREMENT);
  Keyboard.releaseAll();
}
