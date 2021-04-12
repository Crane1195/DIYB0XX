/*
  DIYGCC USB Only v1.209 code by Crane.
  This code utilizes
    MHeironimus' Arduino Joystick Library.
    Arduino Keyboard Library

  This code is for DIY controllers using the Arduino Micro and Leonardo
  without a GameCube circuit.
*/
#include <Joystick.h>
#include <Keyboard.h>

bool isLightShieldButtons = true;
bool UseNewModVertical = true;
bool PrioritizeUP = false; // Priotize up in keyboard mode

enum reportState : byte
{
  ReportOff = 0x30,
  ReportOn = 0x31,
  ReportEnd = 0x0A,
  ReportInvalid = 0x00
};

int reportClock = 0;

typedef struct
{
  bool start;
  bool y;
  bool x;
  bool b;
  bool a;
  bool l;
  bool r;
  bool z;
  bool up;
  bool down;
  bool right;
  bool left;
  bool mod_x;
  bool mod_y;
  bool c_left;
  bool c_right;
  bool c_up;
  bool c_down;
  bool e_1;
  bool e_2;
  bool e_3;
  bool e_4;
  bool e_5;
  bool e_6;
} GCCState;

GCCState controllerState;

uint8_t fTwoIPNoReactivate(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH, bool& lockLOW, bool& lockHIGH);
uint8_t fTwoIP(bool isLOW, bool isHIGH, bool& wasLOW, bool& wasHIGH);
uint8_t fNeutral(bool isLOW, bool isHIGH);

void writeSerialReport();

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  17, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, false,   // Rx, Ry, no Rz
  false, true,          // No rudder, throttle
  false, false, false);  // No accelerator, no brake, no steering

enum game
{
  Melee,
  PM,
  Ultimate,
  RoA
};

enum device
{
	PC,
  Keeb
};

enum SOCD
{
  Neutral,
  TwoIP,
  TwoIPNoReactivate,
  NormalKeyboard,
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

game currentGame = Melee;
device currentDevice = PC;
SOCD currentSOCD = TwoIPNoReactivate;

int L = 16;
int LEFT = 1;
int DOWN = 0;
int RIGHT = 4;
int MODX = 5;
int MODY = 6;

//int SELECT = XX;
int START = 7;
//int HOME = XX;

int CDOWN = 12;
int CLEFT = 9;
int A = 15;
int CUP = 8;
int CRIGHT = 14;

int UP = 13;
int Z = A0;
int X = A1;
int B = A2;

int MIDSHIELD = 10;
int LIGHTSHIELD = 11;
int Y = A3;
int R = A4;

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
  //pinMode(SELECT, INPUT_PULLUP);
  //pinMode(HOME, INPUT_PULLUP);
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

  if (digitalRead(MODY) == LOW) {
    currentDevice = Keeb;
  }

  if (currentDevice == PC) {
    Joystick.begin(false);
    Joystick.setXAxisRange(0, 255);
    Joystick.setYAxisRange(0, 255);
    Joystick.setZAxisRange(0, 255);
    Joystick.setRxAxisRange(0, 255);
    Joystick.setRyAxisRange(0, 255);
    Joystick.setThrottleRange(0, 255);
    Serial.begin(115200, SERIAL_8N1);
  }

  if (currentDevice == Keeb) {
    Keyboard.begin();
    currentSOCD = TwoIP;
  }

  if (digitalRead(B) == LOW)
  {
    currentGame = Ultimate;
    currentSOCD = TwoIP;
  }
  if (digitalRead(X) == LOW)
  {
    currentGame = PM;
    currentSOCD = TwoIPNoReactivate;
  }
  if (digitalRead(Z) == LOW)
  {
    currentGame = RoA;
    currentSOCD = TwoIP;
  }
}

void loop() {
  bool isL           = (digitalRead(L) == LOW);
  bool isLEFT        = (digitalRead(LEFT) == LOW);
  bool isDOWN        = (digitalRead(DOWN) == LOW);
  bool isRIGHT       = (digitalRead(RIGHT) == LOW);
  bool isMODX        = (digitalRead(MODX) == LOW);
  bool isMODY        = (digitalRead(MODY) == LOW);
  bool isSTART       = (digitalRead(START) == LOW);
  //bool isSELECT      = (digitalRead(SELECT) == LOW);
  //bool isHOME        = (digitalRead(HOME) == LOW);
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

  bool is4K = isUP;

  controllerState.l = isL;
  controllerState.left = isLEFT;
  controllerState.down = isDOWN;
  controllerState.right = isRIGHT;
  controllerState.mod_x = isMODX;
  controllerState.mod_y = isMODY;
  controllerState.start = isSTART;
  controllerState.b = isB;
  controllerState.x = isX;
  controllerState.z = isZ;
  controllerState.up = isUP;
  controllerState.r = isR;
  controllerState.y = isY;
  controllerState.c_down = isCDOWN;
  controllerState.a = isA;
  controllerState.c_right = isCRIGHT;
  controllerState.c_left = isCLEFT;
  controllerState.c_up = isCUP;

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

    if (currentDevice == Keeb)
      isUP = isMODX;

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
if (currentDevice != Keeb) { // If Keyboard mode, disregard all modifier logic
    if (isMODX) {
      if (HORIZONTAL) {
        if (currentGame == Melee) controlX = 128 + (positionX * 53);
        if (currentGame == Ultimate) controlX = 128 + (positionX * 40);
        if (currentGame == PM) controlX = 128 + (positionX * 70);
        if (currentGame == RoA) controlX = 128 + (positionX * 66);
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
        if ((currentGame == Melee) || (currentGame == RoA)) {
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
          if ((currentGame == Melee) || (currentGame == RoA)) {
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
          if ((currentGame == Melee) || (currentGame == RoA)) {
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
          if ((currentGame == Melee) || (currentGame == RoA)) {
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
          if ((currentGame == Melee) || (currentGame == RoA)) {
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
        if (currentGame == RoA) controlX = 128 + (positionX * 44);
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
        if (currentGame == RoA) {
          controlX = 128 + (positionX * 44);
          controlY = 128 + (positionY * 113);
        }

        if (isCUP) {
          if ((currentGame == Melee) || (currentGame == RoA)) {
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
          if (currentGame == RoA) {
            controlX = 128 + (positionX * 44);
            controlY = 128 + (positionY * 90);
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
          if (currentGame == RoA) {
            controlX = 128 + (positionX * 44);
            controlY = 128 + (positionY * 74);
          }

        }

        if (isCRIGHT) {
          if ((currentGame == Melee) || (currentGame == RoA)) {
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

    if (isLEFT && isRIGHT && !VERTICAL && (currentGame == Melee))
      controlX = 128 + (positionX * 100);


    if (isLightShieldButtons && (currentGame == Melee)) {
      if (isLIGHTSHIELD || isMIDSHIELD) {
        if (currentDevice == PC) {
          if (isLIGHTSHIELD) RLight = 50;
          if (isMIDSHIELD) RLight = 95;
        }
        else {
          if (isLIGHTSHIELD) RLight = 80;
          if (isMIDSHIELD) RLight = 125;
        }

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
  if (isMODX && isMODY) {
    cstickX = 128;
    cstickY = 128;
    if (isCUP) isDPADUP = true;
    if (isCDOWN) isDPADDOWN = true;
    if (isCLEFT) isDPADLEFT = true;
    if (isCRIGHT) isDPADRIGHT = true;
  }

/*
  if (currentGame == Melee) {
    if (isSELECT) isDPADLEFT = true;
    if (isHOME) isDPADRIGHT = true;
  }
*/

} // End if !Keyboard

/********* PC Dinput Setup *********/

  if (currentDevice == PC) {
    if (currentGame != RoA) {
      Joystick.setButton(0, isA);
      Joystick.setButton(1, isB);
      Joystick.setButton(2, isX);
      Joystick.setButton(3, isY);
      Joystick.setButton(4, isZ);
      Joystick.setButton(5, isL);
      Joystick.setButton(6, isR);
      Joystick.setButton(7, isSTART);
      Joystick.setButton(8, isDPADLEFT);
      Joystick.setButton(9, isDPADUP);
      Joystick.setButton(10, isDPADRIGHT);
      Joystick.setButton(11, isDPADDOWN);
      Joystick.setButton(12, isLIGHTSHIELD);
      Joystick.setButton(13, isMIDSHIELD);

      /*
      if (currentGame != Melee) {
        Joystick.setButton(14, isSELECT);
        Joystick.setButton(15, isHOME);
      }
      */

      Joystick.setXAxis(controlX);
      Joystick.setYAxis(controlY);
      Joystick.setRxAxis(cstickX);
      Joystick.setRyAxis(cstickY);

      if (isLightShieldButtons)
        Joystick.setThrottle(RLight);
      else
        Joystick.setThrottle(LLight);
    }
    else {
      Joystick.setButton(0, isA); //A Check
      //Joystick.setButton(1, isHOME); //B
      Joystick.setButton(2, isB); //X
      Joystick.setButton(3, (isX || isY)); //Y
      Joystick.setButton(4, isZ); //LB
      Joystick.setButton(5, (isL || isR)); //RB
      Joystick.setButton(6, isLIGHTSHIELD); //LB
      Joystick.setButton(7, isMIDSHIELD); //RB
      //Joystick.setButton(8, isSELECT); //Select
      Joystick.setButton(9, isSTART); //Start
      Joystick.setButton(10, (isDPADUP || isDPADDOWN || isDPADLEFT || isDPADRIGHT));

      Joystick.setXAxis(controlX);
      Joystick.setYAxis(((controlY-128) * -1) + 128);
      Joystick.setRxAxis(cstickX);
      Joystick.setRyAxis(((cstickY-128) * -1) + 128);
    }


    if (Serial.availableForWrite() > 32) {
      if (reportClock == 0) {
        writeSerialReport();
        reportClock++;
      }
      else if (reportClock == 3) {
        reportClock = 0;
      }
      else
        reportClock++;
    }

    Joystick.sendState();
  }

  else if (currentDevice == Keeb) {
    /**********************  If keys are pressed **********************/
    if (isL)            Keyboard.press('q');
    if (isMODY)         Keyboard.press('z');

    //if (isSELECT)       Keyboard.press('r');
    if (isSTART)        Keyboard.press('t');
    //if (isHOME)         Keyboard.press('y');

    if (isB)            Keyboard.press('j');
    if (isX)            Keyboard.press('k');
    if (isZ)            Keyboard.press('l');
    if (is4K)           Keyboard.press(';');

    if (isR)            Keyboard.press('u');
    if (isY)            Keyboard.press('i');
    if (isLIGHTSHIELD)  Keyboard.press('o');
    if (isMIDSHIELD)    Keyboard.press('p');

    if (isA)            Keyboard.press('c');
    if (isCUP)          Keyboard.press('v');
    if (isCDOWN)        Keyboard.press('b');
    if (isCLEFT)        Keyboard.press('n');
    if (isCRIGHT)       Keyboard.press('m');

    if (currentSOCD == NormalKeyboard) {
      if (isUP)         Keyboard.press('w');
      if (isLEFT)       Keyboard.press('a');
      if (isDOWN)       Keyboard.press('s');
      if (isRIGHT)      Keyboard.press('d');
    }
    else {
      if (PrioritizeUP && isUP && isDOWN)
        Keyboard.press('w');
      else if (positionY == 1)
        Keyboard.press('w');
      else if (positionY ==-1)
        Keyboard.press('s');

      if (positionX ==-1) Keyboard.press('a');
      if (positionX == 1) Keyboard.press('d');
    }

    /**********************  If keys aren't pressed **********************/
    if (!isL)            Keyboard.release('q');
    if (!isMODY)         Keyboard.release('z');

    //if (!isSELECT)       Keyboard.release('r');
    if (!isSTART)        Keyboard.release('t');
    //if (!isHOME)         Keyboard.release('y');

    if (!isB)            Keyboard.release('j');
    if (!isX)            Keyboard.release('k');
    if (!isZ)            Keyboard.release('l');
    if (!is4K)           Keyboard.release(';');

    if (!isR)            Keyboard.release('u');
    if (!isY)            Keyboard.release('i');
    if (!isLIGHTSHIELD)  Keyboard.release('o');
    if (!isMIDSHIELD)    Keyboard.release('p');

    if (!isA)            Keyboard.release('c');
    if (!isCUP)          Keyboard.release('v');
    if (!isCDOWN)        Keyboard.release('b');
    if (!isCLEFT)        Keyboard.release('n');
    if (!isCRIGHT)       Keyboard.release('m');

    if (currentSOCD == NormalKeyboard) {
      if (!isUP)           Keyboard.release('w');
      if (!isLEFT)         Keyboard.release('a');
      if (!isDOWN)         Keyboard.release('s');
      if (!isRIGHT)        Keyboard.release('d');
    }
    else {

      if (positionX == 1) Keyboard.release('a');
      if (positionX ==-1) Keyboard.release('d');
      if (positionX == 0) {
        Keyboard.release('a');
        Keyboard.release('d');
      }

      if (PrioritizeUP == true) {
        if (isDOWN && isUP)
          Keyboard.release('s');

        if (!isDOWN && isUP)
          Keyboard.release('s');

        if (isDOWN && !isUP)
          Keyboard.release('W');

        if (!isDOWN && !isUP) {
          Keyboard.release('w');
          Keyboard.release('s');
        }

      }
      else {
        if (positionY == 1) Keyboard.release('s');
        if (positionY ==-1) Keyboard.release('w');
        if (positionY == 0) {
          Keyboard.release('w');
          Keyboard.release('s');
        }
      }
    }

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

void writeSerialReport() {
  byte report[25] = {
    controllerState.start ? ReportOn : ReportOff,
    controllerState.y ? ReportOn : ReportOff,
    controllerState.x ? ReportOn : ReportOff,
    controllerState.b ? ReportOn : ReportOff,
    controllerState.a ? ReportOn : ReportOff,
    controllerState.l ? ReportOn : ReportOff,
    controllerState.r ? ReportOn : ReportOff,
    controllerState.z ? ReportOn : ReportOff,
    controllerState.up ? ReportOn : ReportOff,
    controllerState.down ? ReportOn : ReportOff,
    controllerState.right ? ReportOn : ReportOff,
    controllerState.left ? ReportOn : ReportOff,
    controllerState.mod_x ? ReportOn : ReportOff,
    controllerState.mod_y ? ReportOn : ReportOff,
    controllerState.c_left ? ReportOn : ReportOff,
    controllerState.c_right ? ReportOn : ReportOff,
    controllerState.c_up ? ReportOn : ReportOff,
    controllerState.c_down ? ReportOn : ReportOff,
    controllerState.e_1 ? ReportOn : ReportOff,
    controllerState.e_2 ? ReportOn : ReportOff,
    controllerState.e_3 ? ReportOn : ReportOff,
    controllerState.e_4 ? ReportOn : ReportOff,
    controllerState.e_5 ? ReportOn : ReportOff,
    controllerState.e_6 ? ReportOn : ReportOff,
    ReportEnd
  };

  Serial.write(report, 25);
}
