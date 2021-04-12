/*
  DIYGCC USB Only Switch v0.1 code by Crane.
  This code utilizes
    Jas2o's fork of MHeironimus' Arduino Joystick Library.

  This code is for DIY controllers using the Arduino Micro and Leonardo
  without a GameCube circuit.
*/
#include "Joystick.h"

bool isLightShieldButtons = true;
bool UseNewModVertical = true;

uint8_t fTwoIPNoReactivate(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH, bool& lockLOW, bool& lockHIGH);
uint8_t fTwoIP(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH);
uint8_t fNeutral(bool isLOW, bool isHIGH);

/*
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  17, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, false,   // Rx, Ry, no Rz
  false, true,          // No rudder, throttle
  false, false, false);  // No accelerator, no brake, no steering
*/

enum game
{
  Melee,
  PM,
  Ultimate
};

enum device
{
	GC,
	PC
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

game currentGame = Ultimate;
device currentDevice = PC;
SOCD currentSOCD = TwoIP;

int L = 2;
int LEFT = 10;        // Left
int DOWN = 13;        // Down
int RIGHT = 5;        // Right
int MODX = 7;         // Up
int MODY = 3;

int SELECT = 9;       // Select/Share/Back
int START = 6;        // Start/Options
int HOME = 8;         // Home/PS/XB

int CDOWN = A0;
int CLEFT = A1;
int A = A2;
int CUP = A3;
int CRIGHT = A4;

int UP = 15;          // 4K/L2/LT
int Z = 16;           // 3K/R2/RT
int X = 14;           // 2K/O/B
int B = A5;           // 1K/X/A

int MIDSHIELD = 0;    // 4P/L1/LB
int LIGHTSHIELD = 1;  // 3P/R1/RB
int Y = 4;            // 2P/△/Y
int R = 12;           // 1P/□/X

const uint8_t minValue = 28;
const uint8_t maxValue = 228;

void setup() {
  pinMode(L, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(MODX, INPUT_PULLUP);
  pinMode(MODY, INPUT_PULLUP);
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
  if (isLightShieldButtons) {
    pinMode(LIGHTSHIELD, INPUT_PULLUP);
    pinMode(MIDSHIELD, INPUT_PULLUP);
  }

  if (currentDevice == PC) {
    Joystick.begin(false);
    /*
    Joystick.setXAxisRange(0, 255);
    Joystick.setYAxisRange(0, 255);
    Joystick.setRxAxisRange(0, 255);
    Joystick.setRyAxisRange(0, 255);
    Joystick.setThrottleRange(0, 255);
    */
  }

}

void loop()
{
  bool isL           = (digitalRead(L) == LOW);
  bool isLEFT        = (digitalRead(LEFT) == LOW);
  bool isDOWN        = (digitalRead(DOWN) == LOW);
  bool isRIGHT       = (digitalRead(RIGHT) == LOW);
  bool isMODX        = (digitalRead(MODX) == LOW);
  bool isMODY        = (digitalRead(MODY) == LOW);
  bool isSTART       = (digitalRead(START) == LOW);
  bool isSELECT      = (digitalRead(SELECT) == LOW);
  bool isHOME        = (digitalRead(HOME) == LOW);
  bool isB           = (digitalRead(B) == LOW);
  bool isX           = (digitalRead(X) == LOW);
  bool isZ           = (digitalRead(Z) == LOW);
  bool isUP          = (digitalRead(UP) == LOW);
  bool isR           = (digitalRead(R) == LOW);
  bool isY           = (digitalRead(Y) == LOW);
  bool isLIGHTSHIELD = (digitalRead(LIGHTSHIELD) == LOW);
  bool isMIDSHIELD   = (digitalRead(MIDSHIELD) == LOW);
  bool isCDOWN       = (digitalRead(CDOWN) == LOW);
  bool isA           = (digitalRead(A) == LOW);
  bool isCRIGHT      = (digitalRead(CRIGHT) == LOW);
  bool isCLEFT       = (digitalRead(CLEFT) == LOW);
  bool isCUP         = (digitalRead(CUP) == LOW);



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

    /********* SOCD *********/
    if (currentSOCD == TwoIPNoReactivate) {
      controlX = fTwoIPNoReactivate(isLEFT, isRIGHT, wasLEFT, wasRIGHT, lockLEFT, lockRIGHT);
      controlY = fTwoIPNoReactivate(isDOWN, isUP, wasDOWN, wasUP, lockDOWN, lockUP);
      cstickX = fTwoIPNoReactivate(isCLEFT, isCRIGHT, wasCLEFT, wasCRIGHT, lockCLEFT, lockCRIGHT);
      cstickY = fTwoIPNoReactivate(isCDOWN, isCUP, wasCDOWN, wasCUP, lockCDOWN, lockCUP);
    }

    if (currentSOCD == TwoIP){
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

    if (isMODX) {
      if (HORIZONTAL) {
        if (currentGame == Melee) controlX = 128 + (positionX * 53);
        if (currentGame == Ultimate) controlX = 128 + (positionX * 40);
        if (currentGame == PM) controlX = 128 + (positionX * 70);
      }
      if (VERTICAL) {
        if (currentGame == Melee) {
          if (UseNewModVertical)
            controlY = 128 + (positionY * 23);
          else
            controlY = 128 + (positionY * 52);
        }
        if (currentGame == Ultimate) controlY = 128 + (positionY * 49);
        if (currentGame == PM) controlY = 128 + (positionY * 60);
      }

      if (isB) {
        if (currentGame == Melee) controlX = 128 + (positionX * 53);
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 47);
          controlY = 128 + (positionY * 41);
        }
      }
      if (positionCX != 0){
        cstickX = 128 + (positionCX * 65);
        cstickY = 128 + (positionY * 23);
      }

      if (DIAGONAL) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 59);
          controlY = 128 + (positionY * 23);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 40);
          controlY = 128 + (positionY * 26);
          if (isB) controlX = 128 + (positionX * 53);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 70);
          controlY = 128 + (positionY * 34);
        }

        if (isCUP) {
          if (currentGame == Melee) {
            controlX = 128 + (positionX * 49);
            controlY = 128 + (positionY * 35);
          }
          if (currentGame == Ultimate) {
            controlX = 128 + (positionX * 71);
            controlY = 128 + (positionY * 35);
          }
          if (currentGame == PM) {
            controlX = 128 + (positionX * 77);
            controlY = 128 + (positionY * 55);
          }
        }

        if (isCDOWN) {
          if (currentGame == Melee) {
            controlX = 128 + (positionX * 49);
            controlY = 128 + (positionY * 24);
          }
          if (currentGame == Ultimate) {
            controlX = 128 + (positionX * 61);
            controlY = 128 + (positionY * 49);
          }
          if (currentGame == PM) {
            controlX = 128 + (positionX * 82);
            controlY = 128 + (positionY * 32);
          }
        }

        if (isCLEFT) {
          if (currentGame == Melee) {
            controlX = 128 + (positionX * 52);
            controlY = 128 + (positionY * 31);
          }
          if (currentGame == Ultimate) {
            controlX = 128 + (positionX * 66);
            controlY = 128 + (positionY * 42);
          }
          if (currentGame == PM) {
            controlX = 128 + (positionX * 84);
            controlY = 128 + (positionY * 50);
          }
        }

        if (isCRIGHT) {
          if (currentGame == Melee) {
            controlX = 128 + (positionX * 51);
            controlY = 128 + (positionY * 43);
          }
          if (currentGame == Ultimate) {
            controlX = 128 + (positionX * 75);
            controlY = 128 + (positionY * 27);
          }
          if (currentGame == PM) {
            controlX = 128 + (positionX * 72);
            controlY = 128 + (positionY * 61);
          }
        }
      }
    }

    if (isMODY) {
      if (HORIZONTAL) {
        if (currentGame == Melee) controlX = 128 + (positionX * 27);
        if (currentGame == Ultimate) controlX = 128 + (positionX * 27);
        if (currentGame == PM) controlX = 128 + (positionX * 28);
      }
      if (VERTICAL) {
        if (currentGame == Melee) controlY = 128 + (positionY * 59);
        if (currentGame == Ultimate) controlY = 128 + (positionY * 51);
        if (currentGame == PM) controlY = 128 + (positionY * 34);
      }

      if (isB) {
        if (currentGame == Melee) controlX = 128 + (positionX * 80);
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 41);
          controlY = 128 + (positionY * 61);
        }
        if (currentGame == PM) controlX = 128 + (positionX * 59);
      }

      if (DIAGONAL) {
        if (currentGame == Melee) {
          controlX = 128 + (positionX * 23);
          controlY = 128 + (positionY * 59);
        }
        if (currentGame == Ultimate) {
          controlX = 128 + (positionX * 38);
          controlY = 128 + (positionY * 49);
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 28);
          controlY = 128 + (positionY * 58);
        }

        if (isCUP) {
          if (currentGame == Melee) {
            controlX = 128 + (positionX * 45);
            controlY = 128 + (positionY * 63);
          }
          if (currentGame == Ultimate) {
            controlX = 128 + (positionX * 35);
            controlY = 128 + (positionY * 71);
          }
          if (currentGame == PM) {
            controlX = 128 + (positionX * 55);
            controlY = 128 + (positionY * 77);
          }
        }

        if (isCDOWN) {
          if (currentGame == Melee) {
            controlX = 128 + (positionX * 28);
            controlY = 128 + (positionY * 57);
          }
          if (currentGame == Ultimate) {
            controlX = 128 + (positionX * 49);
            controlY = 128 + (positionY * 61);
          }
          if (currentGame == PM) {
            controlX = 128 + (positionX * 32);
            controlY = 128 + (positionY * 82);
          }
        }

        if (isCLEFT) {
          if (currentGame == Melee) {
            controlX = 128 + (positionX * 34);
            controlY = 128 + (positionY * 57);
          }
          if (currentGame == Ultimate) {
            controlX = 128 + (positionX * 42);
            controlY = 128 + (positionY * 66);
          }
          if (currentGame == PM) {
            controlX = 128 + (positionX * 50);
            controlY = 128 + (positionY * 84);
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
            controlX = 128 + (positionX * 62);
            controlY = 128 + (positionY * 72);
          }
        }
      }
    }

    if (isLEFT && isRIGHT && !VERTICAL)
      controlX = 128 + (positionX * 100);


    if (isLightShieldButtons && (currentGame == Melee)) {
      if (isLIGHTSHIELD || isMIDSHIELD) {
        if (isLIGHTSHIELD) RLight = 49;
        if (isMIDSHIELD) RLight = 94;

        if (HORIZONTAL && (positionY == -1)) {
          controlX = 128 + (positionX * 57);
          controlY = 128 - 55;
        }

        if (isMODX) {
          if (HORIZONTAL) {
            if (currentGame == Ultimate)
              controlX = 128 + (positionX * 51);
            if (currentGame == Melee)
              controlX = 128 + (positionX * 51);
            if (currentGame == PM)
              controlX = 128 + (positionX * 48);
          }

          if (VERTICAL) {
            if (currentGame == Ultimate)
              controlY = 128 + (positionY * 51);
            if (currentGame == Melee)
              controlY = 128 + (positionY * 43);
            if (currentGame == PM)
              controlY = 128 + (positionY * 48);
          }

          if (DIAGONAL)
            if (currentGame == Melee) controlX = 128 + (positionX * 43);

        }
      }
    }

    if (isL) {
      LLight = 140;
      if (HORIZONTAL) controlX = 128 + (positionX * 100);
      if (VERTICAL) controlY = 128 + (positionY * 100);
      if (HORIZONTAL && (positionY == 1)) {
        if (currentGame == Melee){
          controlX = 128 + (positionX * 43);
          controlY = 128 + 43;
        }
        if (currentGame == PM) {
          controlX = 128 + (positionX * 67);
          controlY = 128 + 67;
        }
      }
      if (HORIZONTAL && (positionY == -1)) {
        controlX = 128 + (positionX * 57);
        if (currentGame == Melee) controlY = 128 - 55;
        else {controlX = 128 + (positionX * 100); controlY = minValue;}
      }
      if ((currentGame == Melee) && (isMODX || isMODY)) {
        if (!isLightShieldButtons) {
          if (!(isMODX && isMODY)) {
            isL = false;
            LLight = 80;
          }
        }

        if (DIAGONAL) {
          if (isMODX) {
            controlX = 128 + (positionX * 51);
            controlY = 128 + (positionY * 30);
          }
          if (isMODY) {
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
        if (currentGame == Melee)
          controlX = 128 + (positionX * 51);
        if (currentGame == PM)
          controlX = 128 + (positionX * 48);
      }
      if (VERTICAL) {
        if (currentGame == Ultimate)
          controlY = 128 + (positionY * 51);
        if (currentGame == Melee)
          controlY = 128 + (positionY * 43);
        if (currentGame == PM)
          controlY = 128 + (positionY * 48);
      }
      if (DIAGONAL) {
        if (currentGame == Melee) controlX = 128 + (positionX * 43);
        if (isMODX) {
          if (currentGame == Melee){
            controlX = 128 + (positionX * 51);
            controlY = 128 + (positionY * 30);
          }
          if (currentGame == PM){
            controlX = 128 + (positionX * 68);
            controlY = 128 + (positionY * 40);
          }
        }
        if (isMODY) {
          controlX = 128 + (positionX * 40);
          controlY = 128 + (positionY * 68);
        }
      }
    }

/********* DPAD *********/
//Comment out line 588, and uncomment 589 if you want to use a dpad switch/button on the MIDSHIELD terminal.
  if (isMODX && isMODY) {
  //if (isMIDSHIELD) {
    cstickX = 128;
    cstickY = 128;
    if (isCUP) isDPADUP = true;
    if (isCDOWN) isDPADDOWN = true;
    if (isCLEFT) isDPADLEFT = true;
    if (isCRIGHT) isDPADRIGHT = true;
  }
/********* PC Dinput Setup *********/

  if (currentDevice == PC) {
    // Face buttons
    Joystick.setButton(2, isA);
    Joystick.setButton(1, isB);
    Joystick.setButton(3, isX);
    Joystick.setButton(0, isY);

    // Shoulder buttons
    if (isZ || isMIDSHIELD)
      Joystick.setButton(5, 1);
    else
      Joystick.setButton(5, 0);

    Joystick.setButton(4, isLIGHTSHIELD);

    // Triggers
    Joystick.setButton(6, isL);
    Joystick.setButton(7, isR);

    // Function buttons
    Joystick.setButton(9, isSTART);
    Joystick.setButton(8, isSELECT);
    Joystick.setButton(12, isHOME);
    if (isMODX && isMODY && isSTART && isSELECT && isHOME)
      Joystick.setButton(13, 1);

    // Dpad buttons
    if (isDPADUP)
      Joystick.setHatSwitch(0);
    else if (isDPADRIGHT)
      Joystick.setHatSwitch(2);
    else if (isDPADDOWN)
      Joystick.setHatSwitch(4);
    else if (isDPADLEFT)
      Joystick.setHatSwitch(6);
    else
      Joystick.setHatSwitch(-1);

    // Control sticks
    Joystick.setXAxis(1.27*(controlX-128));
    Joystick.setYAxis(-1.27*(controlY-128));
    Joystick.setZAxis(1.27*(cstickX-128));
    Joystick.setZAxisRotation(-1.27*(cstickY-128));

    Joystick.sendState();
    delay(1);
  }
}

uint8_t fTwoIPNoReactivate(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH, bool& lockLOW, bool& lockHIGH){
  uint8_t control = 128;
  if (isLOW && isHIGH) {
    if (wasHIGH) {
      control = minValue;
      lockHIGH = true; }
    if (wasLOW) {
      control = maxValue;
      lockLOW = true; }
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

uint8_t fTwoIP(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH){
  uint8_t control = 128;
  if (isLOW && wasHIGH)
    control = minValue;
  if (isHIGH && wasLOW)
    control = maxValue;
  if (!isLOW && isHIGH) {
    control = maxValue;
    wasHIGH = true;
    wasLOW = false; }
  if (isLOW && !isHIGH) {
    control = minValue;
    wasLOW = true;
    wasHIGH = false;
  }
  return control;
}

uint8_t fNeutral(bool isLOW, bool isHIGH){
  uint8_t control = 128;
  if (!isLOW && isHIGH)
    control = maxValue;
  if (isLOW && !isHIGH)
    control = minValue;
  return control;
}
