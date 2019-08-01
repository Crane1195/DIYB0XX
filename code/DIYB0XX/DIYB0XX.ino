/*
  DIY B0XX v1.0 code by Crane.
  This code utilizes
    Nicohood's Nintendo library

  This is code designed with 16 mhz Arduinos in mind such as the Arduino Mega 2560, Arduino Micro, Arduino Nano, etc.
  A version of this code is available with native USB joystick support and nunchuk support for controllers using the 32u4
  chip such as my Arduino Micro based GCCPCB. You can probably use it on a Micro/Leonardo/Pro Micro DIY, but do so at your own risk.
  Heres a link to it : https://github.com/Crane1195/GCCPCB/tree/master/code

  Read the README file for whichever of these you are using for more information.
*/
#include "Nintendo.h"

uint8_t fTwoIPNoReactivate(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH, bool& lockLOW, bool& lockHIGH);
uint8_t fTwoIP(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH);
uint8_t fNeutral(bool isLOW, bool isHIGH);

// Change the number inside the parentheses to whichever pin you have your data line plugged into.
CGamecubeConsole GamecubeConsole(A5);
Gamecube_Data_t d = defaultGamecubeData;

enum game
{
  Melee,
  PM,
  Ultimate
};

enum SOCD
{
  Neutral,
  TwoIP,
  TwoIPNoReactivate
};

bool wasLEFT = false;
bool wasRIGHT = false;
bool wasUP = false;
bool wasDOWN = false;

bool wasCLEFT = false;
bool wasCRIGHT = false;
bool wasCUP = false;
bool wasCDOWN = false;

bool lockLEFT = false;
bool lockRIGHT = false;
bool lockUP = false;
bool lockDOWN = false;

bool lockCLEFT = false;
bool lockCRIGHT = false;
bool lockCUP = false;
bool lockCDOWN = false;

// This is the mode that will occur when you plug in while holding down nothing.
// Change it if you want to.
game currentGame = Melee;
SOCD currentSOCD = TwoIPNoReactivate;

// Here are your pin assignments. Change the number after the equals sign to wherever each button is plugged into.
const int L = 16;
const int LEFT = 1;
const int DOWN = 0;
const int RIGHT = 4;
const int MOD1 = 5;
const int MOD2 = 6;

const int START = 7;
const int B = A2;
const int X = A1;
const int Z = A0;
const int UP = 13;
const int R = A4;
const int Y = A3;

const int CDOWN = 12;
const int A = 15;
const int CRIGHT = 14;
const int CLEFT = 9;
const int CUP = 8;

//const int DPADSWITCH = XX;

const uint8_t minValue = 48;
const uint8_t maxValue = 208;

void setup()
{
  pinMode(L, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(MOD1, INPUT_PULLUP);
  pinMode(MOD2, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(Z, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(R, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(CDOWN, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(CRIGHT, INPUT_PULLUP);
  pinMode(CLEFT, INPUT_PULLUP);
  pinMode(CUP, INPUT_PULLUP);
  //pinMode(DPADSWITCH, INPUT_PULLUP);

  // Here are the settings for a second mode. By default, holding B while plugging in switches
  // to Ultimate, with 2ip no reactivation. Change any of these you want to.
  if (digitalRead(B) == LOW)
  {
    currentGame = Ultimate;
    currentSOCD = TwoIPNoReactivate;
  }

  // Here are the settings for a third mode. By default, holding X while plugging in switches
  // to PM, with 2ip no reactivation. Change any of these you want to.
  if (digitalRead(X) == LOW)
  {
    currentGame = PM;
    currentSOCD = TwoIPNoReactivate;
  }
}

void loop()
{
  bool isL          = (digitalRead(L) == LOW);
  bool isLEFT       = (digitalRead(LEFT) == LOW);
  bool isDOWN       = (digitalRead(DOWN) == LOW);
  bool isRIGHT      = (digitalRead(RIGHT) == LOW);
  bool isMOD1       = (digitalRead(MOD1) == LOW);
  bool isMOD2       = (digitalRead(MOD2) == LOW);
  bool isSTART      = (digitalRead(START) == LOW);
  bool isB          = (digitalRead(B) == LOW);
  bool isX          = (digitalRead(X) == LOW);
  bool isZ          = (digitalRead(Z) == LOW);
  bool isUP         = (digitalRead(UP) == LOW);
  bool isR          = (digitalRead(R) == LOW);
  bool isY          = (digitalRead(Y) == LOW);
  bool isCDOWN      = (digitalRead(CDOWN) == LOW);
  bool isA          = (digitalRead(A) == LOW);
  bool isCRIGHT     = (digitalRead(CRIGHT) == LOW);
  bool isCLEFT      = (digitalRead(CLEFT) == LOW);
  bool isCUP        = (digitalRead(CUP) == LOW);
  //bool isDPADSWITCH = (digitalRead(DPADSWITCH) == LOW);

  bool isDPADUP = false;
  bool isDPADDOWN = false;
  bool isDPADLEFT = false;
  bool isDPADRIGHT = false;

  uint8_t controlX = 128;
  uint8_t controlY = 128;
  uint8_t cstickX = 128;
  uint8_t cstickY = 128;
  uint8_t RLight = 0;
  uint8_t LLight = 0;

  int8_t positionX = 0;
  int8_t positionY = 0;
  int8_t positionCX = 0;
  int8_t positionCY = 0;

  bool HORIZONTAL = false;
  bool VERTICAL = false;
  bool DIAGONAL = false;
  bool paluShorten = false;

  /********* SOCD *********/
  if (currentSOCD == TwoIPNoReactivate) {
    controlX = fTwoIPNoReactivate(isLEFT, isRIGHT, wasLEFT, wasRIGHT, lockLEFT, lockRIGHT);
    controlY = fTwoIPNoReactivate(isDOWN, isUP, wasDOWN, wasUP, lockDOWN, lockUP);
    cstickX = fTwoIPNoReactivate(isCLEFT, isCRIGHT, wasCLEFT, wasCRIGHT, lockCLEFT, lockCRIGHT);
    cstickY = fTwoIPNoReactivate(isCDOWN, isCUP, wasCDOWN, wasCUP, lockCDOWN, lockCUP);
  }

  if (currentSOCD == TwoIP) {
    controlX = fTwoIP(isLEFT, isRIGHT, wasLEFT, wasRIGHT);
    controlY = fTwoIP(isDOWN, isUP, wasDOWN, wasUP);
    cstickX = fTwoIP(isCLEFT, isCRIGHT, wasCLEFT, wasCRIGHT);
    cstickY = fTwoIP(isCDOWN, isCUP, wasCDOWN, wasCUP);
  }

  if (currentSOCD == Neutral) {
    controlX = fNeutral(isLEFT, isRIGHT);
    controlY = fNeutral(isDOWN, isUP);
    cstickX = fNeutral(isCLEFT, isCRIGHT);
    cstickY = fNeutral(isCDOWN, isCUP);
  }

  if (controlX != 128) {
    HORIZONTAL = true;
    if (controlX == minValue) positionX = -1;
    else positionX = 1;
  }
  if (controlY != 128) {
    VERTICAL = true;
    if (controlY == minValue) positionY = -1;
    else positionY = 1;
  }
  if (HORIZONTAL && VERTICAL) DIAGONAL = true;

  if (cstickX != 128) {
    if (cstickX == minValue) positionCX = -1;
    else positionCX = 1;
  }
  if (cstickY != 128) {
    if (cstickY == minValue) positionCY = -1;
    else positionCY = 1;
  }

  /********* Modifiers *********/
  if (isMOD1) {
    if (HORIZONTAL) {
      if (currentGame == Melee) controlX = 128 + (positionX * 59);
      if (currentGame == Ultimate) controlX = 128 + (positionX * 40);
      if (currentGame == PM) controlX = 128 + (positionX * 49);
    }
    if (VERTICAL) {
      if (currentGame == Melee) controlY = 128 + (positionY * 52);
      if (currentGame == Ultimate) controlY = 128 + (positionY * 49);
      if (currentGame == PM) controlY = 128 + (positionY * 65);
    }
    if (isA) {
      if (currentGame == Melee) controlX = 128 + (positionX * 47);
      if (currentGame == Ultimate) controlX = 128 + (positionX * 47);
      if (currentGame == PM) controlX = 128 + (positionX * 47);
    }
    if (isB) {
      if (currentGame == Melee) controlX = 128 + (positionX * 59);
      if (currentGame == Ultimate) {
        controlX = 128 + (positionX * 47);
        controlY = 128 + (positionY * 41);
      }
      if (currentGame == PM) controlX = 128 + (positionX * 59);
    }
    if (positionCX != 0) {
      cstickX = 128 + (positionCX * 65);
      cstickY = 128 + 40;
    }
    if (DIAGONAL) {
      if (currentGame == Melee) {
        controlX = 128 + (positionX * 59);
        controlY = 128 + (positionY * 23);
      }
      if (currentGame == Ultimate) {
        controlX = 128 + (positionX * 40);
        controlY = 128 + (positionY * 40);
        if (isB) controlX = 128 + (positionX * 53);
      }
      if (currentGame == PM) {
        controlX = 128 + (positionX * 68);
        controlY = 128 + (positionY * 28);
      }

      if (isCUP) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 53);
          controlY = 128 + (positionY * 37);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 71);
          controlY = 128 + (positionY * 35);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 53);
          controlY = 128 + (positionY * 37);
        }
      }

      if (isCDOWN) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 62);
          controlY = 128 + (positionY * 30);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 61);
          controlY = 128 + (positionY * 49);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 62);
          controlY = 128 + (positionY * 30);
        }
      }

      if (isCLEFT) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 63);
          controlY = 128 + (positionY * 37);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 66);
          controlY = 128 + (positionY * 42);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 63);
          controlY = 128 + (positionY * 37);
        }
      }

      if (isCRIGHT) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 51);
          controlY = 128 + (positionY * 42);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 75);
          controlY = 128 + (positionY * 27);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 51);
          controlY = 128 + (positionY * 42);
        }
      }

      if (isL && (currentGame == Ultimate)) {
        if ((positionCX == 0) && (positionCY == 0)) {
          controlX = ((controlX - 128) * 0.9) + 128;
          controlY = ((controlY - 128) * 0.9) + 128;
        }
        else if (positionCX == 1) { /********/
          cstickX = 128;
          cstickY = 128 + 80;
          controlX = 128 + (positionX * 45);
          controlY = 128 + (positionY * 22);
        }
        else if (positionCY == -1) { /********/
          cstickX = 128;
          cstickY = 128 - 20;
          controlX = 128 + (positionX * 42);
          controlY = 128 + (positionY * 26);
        }
        else {
          controlX = ((controlX - 128) * 0.6375) + 128;
          controlY = ((controlY - 128) * 0.6375) + 128;
        }
        paluShorten = true;
      }
    }
  }

  if (isMOD2) {
    if (HORIZONTAL) {
      if (currentGame == Melee) controlX = 128 + (positionX * 23);
      if (currentGame == Ultimate) controlX = 128 + (positionX * 27);
      if (currentGame == PM) controlX = 128 + (positionX * 33);
    }
    if (VERTICAL) {
      if (currentGame == Melee) controlY = 128 + (positionY * 59);
      if (currentGame == Ultimate) controlY = 128 + (positionY * 51);
      if (currentGame == PM) controlY = 128 + (positionY * 59);
    }
    if (isA) {
      if (currentGame == Melee) controlX = 128 + (positionX * 35);
      if (currentGame == Ultimate) controlX = 128 + (positionX * 41);
      if (currentGame == PM) controlX = 128 + (positionX * 35);
    }
    if (isB) {
      if (currentGame == Melee) controlX = 128 + (positionX * 59);
      if (currentGame == Ultimate) {
        controlX = 128 + (positionX * 41);
        controlY = 128 + (positionY * 61);
      }
      if (currentGame == PM) controlX = 128 + (positionX * 59);
    }
    if (positionCX != 0) {
      cstickX = 128 + (positionCX * 65);
      cstickY = 128 - 40;
    }
    if (DIAGONAL) {
      if (currentGame == Melee) {
        controlX = 128 + (positionX * 23);
        controlY = 128 + (positionY * 59);
      }
      if (currentGame == Ultimate) {
        controlX = 128 + (positionX * 39);
        controlY = 128 + (positionY * 51);
      }
      if (currentGame == PM) {
        controlX = 128 + (positionX * 28);
        controlY = 128 + (positionY * 68);
      }

      if (isCUP) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 44);
          controlY = 128 + (positionY * 63);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 35);
          controlY = 128 + (positionY * 71);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 44);
          controlY = 128 + (positionY * 63);
        }
      }

      if (isCDOWN) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 31);
          controlY = 128 + (positionY * 64);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 49);
          controlY = 128 + (positionY * 61);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 31);
          controlY = 128 + (positionY * 64);
        }
      }

      if (isCLEFT) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 37);
          controlY = 128 + (positionY * 63);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 42);
          controlY = 128 + (positionY * 66);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 37);
          controlY = 128 + (positionY * 63);
        }
      }

      if (isCRIGHT) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 47);
          controlY = 128 + (positionY * 57);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 27);
          controlY = 128 + (positionY * 75);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 47);
          controlY = 128 + (positionY * 57);
        }
      }

      if (isL && (currentGame == Ultimate)) {
        if ((positionCX == 0) && (positionCY == 0)) {
          controlX = ((controlX - 128) * 0.9) + 128;
          controlY = ((controlY - 128) * 0.9) + 128;
        }
        else if ((positionCX == 1) || (positionCY == 1)) {
          controlX = 128 + (positionX * 26);
          controlY = 128 + (positionY * 42);
        }
        else {
          controlX = ((controlX - 128) * 0.6375) + 128;
          controlY = ((controlY - 128) * 0.6375) + 128;
        }
        paluShorten = true;
      }
    }
  }

  if (isL && (paluShorten == false)) {
    LLight = 140;
    if (HORIZONTAL) controlX = 128 + (positionX * 80);
    if (VERTICAL) controlY = 128 + (positionY * 80);
    if (HORIZONTAL && (positionY == 1)) {
      controlX = 128 + (positionX * 52);
      controlY = 128 + 52;
    }
    if (HORIZONTAL && (positionY == -1)) {
      controlX = 128 + (positionX * 58);
      if (currentGame == Melee) controlY = 128 - 55;
      else {controlX = 128 + (positionX * 80); controlY = minValue};
    }
    if (isMOD1 || isMOD2) {
      isL = false;
      LLight = 80;
      if (DIAGONAL) {
        if (isMOD1) {
          controlX = 128 + (positionX * 68);
          controlY = 128 + (positionY * 40);
        }
        if (isMOD2) {
          controlX = 128 + (positionX * 40);
          controlY = 128 + (positionY * 68);
        }
      }
    }
  }

  if (isR) {
    RLight = 140;
    if (HORIZONTAL) {
      if (currentGame == Ultimate)
        controlX = 128 + (positionX * 51);
      else
        controlX = 128 + (positionX * 55);
    }
    if (VERTICAL) {
      if (currentGame == Ultimate)
        controlY = 128 + (positionY * 51);
      else
        controlY = 128 + (positionY * 52);
    }
    if (DIAGONAL)
      if (currentGame != Ultimate) controlX = 128 + (positionX * 52);
    if (HORIZONTAL && isDOWN) {
      if (isMOD1) {
        controlX = 128 + (positionX * 68);
        controlY = 128 + (positionY * 40);
      }
      if (isMOD2) {
        controlX = 128 + (positionX * 40);
        controlY = 128 + (positionY * 68);
      }
    }
  }

  /********* DPAD *********/
  if (isMOD1 && isMOD2) {
  //if (isDPADSWITCH) {
    cstickX = 128;
    cstickY = 128;
    if (isCUP) isDPADUP = true;
    if (isCDOWN) isDPADDOWN = true;
    if (isCLEFT) isDPADLEFT = true;
    if (isCRIGHT) isDPADRIGHT = true;
  }

  /********* GC Report *********/
  d.report.l = isL;
  d.report.start = isSTART;
  d.report.b = isB;
  d.report.x = isX;
  d.report.z = isZ;
  d.report.r = isR;
  d.report.y = isY;
  d.report.a = isA;
  d.report.dup = isDPADUP;
  d.report.ddown = isDPADDOWN;
  d.report.dleft = isDPADLEFT;
  d.report.dright = isDPADRIGHT;

  d.report.xAxis = controlX;
  d.report.yAxis = controlY;
  d.report.cxAxis = cstickX;
  d.report.cyAxis = cstickY;
  d.report.right = RLight;
  d.report.left = LLight;
  GamecubeConsole.write(d);
}

uint8_t fTwoIPNoReactivate(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH, bool& lockLOW, bool& lockHIGH) {
  uint8_t control = 128;
  if (isLOW && isHIGH) {
    if (wasHIGH) {
      control = minValue;
      lockHIGH = true;
    }
    if (wasLOW) {
      control = maxValue;
      lockLOW = true;
    }
  }
  if (!isLOW && isHIGH && (lockHIGH == false)) {
    control = maxValue;
    wasHIGH = true;
    wasLOW = false;
    lockLOW = false;
  }
  if (isLOW && !isHIGH && (lockLOW == false)) {
    control = minValue;
    wasLOW = true;
    wasHIGH = false;
    lockHIGH = false;
  }
  if (!isLOW && !isHIGH) {
    wasHIGH = false;
    wasLOW = false;
    lockLOW = false;
    lockHIGH = false;
  }
  return control;
}

uint8_t fTwoIP(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH) {
  uint8_t control = 128;
  if (isLOW && wasHIGH)
    control = minValue;
  if (isHIGH && wasLOW)
    control = maxValue;
  if (!isLOW && isHIGH) {
    control = maxValue;
    wasHIGH = true;
    wasLOW = false;
  }
  if (isLOW && !isHIGH) {
    control = minValue;
    wasLOW = true;
    wasHIGH = false;
  }
  return control;
}

uint8_t fNeutral(bool isLOW, bool isHIGH) {
  uint8_t control = 128;
  if (!isLOW && isHIGH)
    control = maxValue;
  if (isLOW && !isHIGH)
    control = minValue;
  return control;
}
