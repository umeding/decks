/*
   Configurations
*/

#pragma once

#include <Keyboard.h>

#include "Private.h"

// ----------------------------------------
// Arduino Micro Pro

#define RXLED 17
#define TXLED 30

#define KILL_SWITCH_PIN 10

// Mini Deck Keys -> pin number map
//
// +---+---+    +---+---+
// | 1 | 2 |    | 7 | 2 |
// +---+---+    +---+---+
// | 3 | 4 |    | 6 | 3 |
// +---+---+    +---+---+
// | 5 | 6 |    | 5 | 4 |
// +---+---+    +---+---+
//

#define MDK1 7
#define MDK2 2
#define MDK3 6
#define MDK4 3
#define MDK5 5
#define MDK6 4
