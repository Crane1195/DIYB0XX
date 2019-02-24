#include "Nintendo.h"
/* This code uses the Nicohood Library
 * Use this code at your own risk
 * Code written by Simple Controllers and this code is open source.
 * Meaning its free to share, improve on, or anything you like!
 * Just remember to mention you used my code!
 * Edited by Danny for SmashB0XX
 *
 * [Crane]
 * For Smash4/U mode,
 *  Mod running, tilts, triggers(shields), and most firefox angles edited.
 *  Mods change running/walking speed. Direction, then mod1 gives perfect speed to ledgerun in smash4.
 *  Tilts now work with mod1.
 *  Triggers now give the analog value needed to shield in smash4/Ultimate. LRAStart now works too because of this
 *  FFox angles (b0xx method, c stick) now almost work properly. only mod1+diagonal+cright/left do not work (in smash4, not Ultimate). Can't figure out why.
    C stickless firefox angles function now.
 *
 * For Project M mode
 *  Tilts, firefox angles, shield drop angles (Axe method), and wavedash angles all fixed.
 *  Fixed bug where left and down were not working on SSS and menus.
 *
 *  All three modes are in this one program, so you don't have to keep swapping.
 *
 *  To launch in Melee mode, just plug in normally
 *  To launch in Ultimate/4 mode, hold B while plugging in.
 *  To launch in Project M mode, hold X while plugging in.
 *
 * Be sure to button check before starting a set, to confirm you are in the right mode.
 * If mod1+up makes you jump, or if mod1+down+B makes you neutral B, you are in the wrong mode. Check both of these.
 */
//This makes the controller bidirection data line on pin number8
CGamecubeConsole GamecubeConsole(8);      //Defines a "Gamecube Console" sending data to the console on pin 8
Gamecube_Data_t d = defaultGamecubeData;   //Structure for data to be sent to console

enum game
{
  Melee,
  PM,
  Ultimate
};

//This is needed but you don't need a controller on pin 7
CGamecubeController GamecubeController1(7);

//This is the pinout of the controller.  Can be changed to your liking.  I may have mixed up some of the tilt pins but you can change that physically in your build or through the code.  Just do test runs along the way.
const int A = 46;
const int B = 44;
const int X = 49;
const int Y = 31;
const int Z = 41;
const int START = 39;

const int R = 24;
const int L = 34;
//const int RLIGHT = 36; Only if using LightShield Button
//This is the value of analog shielding 74 is lightest possible on gamecube.  It varies from gamecube to dolphin no idea why.
//const int RLIGHTv = 74;

const int LEFT = 26;
const int RIGHT = 40;
const int UP = 48;
const int DOWN = 35;

const int MOD1 = 38;
const int MOD2 = 22;

const int CLEFT = 28;
const int CRIGHT = 50;
const int CUP = 30;
const int CDOWN = 51;

bool isLeft = false;
bool isRight = true;

game currentGame = Melee;

void setup()
{
  //This is establishing the pin assignments up there to input pins
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(Z, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);

  pinMode(R, INPUT_PULLUP);
  pinMode(L, INPUT_PULLUP);
  //pinMode(RLIGHT, INPUT_PULLUP);

  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);

  pinMode(MOD1, INPUT_PULLUP);
  pinMode(MOD2, INPUT_PULLUP);

  pinMode(CLEFT, INPUT_PULLUP);
  pinMode(CRIGHT, INPUT_PULLUP);
  pinMode(CUP, INPUT_PULLUP);
  pinMode(CDOWN, INPUT_PULLUP);

  //this is just to turn off built in LED at start
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  if (digitalRead(B) == LOW)
    currentGame = Ultimate;
  if (digitalRead(X) == LOW)
    currentGame = PM;



  //This is needed to run the code.
  GamecubeController1.read();
}

void loop()
{
  //This resets and establishes all the values after the controller sends them to the console and helps with initial "zeroing"
  int pinA = 0;
  int pinB = 0;
  int pinX = 0;
  int pinY = 0;
  int pinZ = 0;
  int pinSTART = 0;

  int pinR = 0;
  int pinL = 0;
  int pinRLIGHT = 0;
  int pinLLIGHT = 0;

  int pinDLEFT = 0;
  int pinDRIGHT = 0;
  int pinDUP = 0;
  int pinDDOWN = 0;

  int mod1 = 0;
  int mod2 = 0;

  int pinCLEFT = 0;
  int pinCRIGHT = 0;
  int pinCUP = 0;
  int pinCDOWN = 0;

  int pinxAxisC = 128;
  int pinyAxisC = 128;

  int pinxAxis = 128;
  int xmod = 0;
  int pinyAxis = 128;

  int rightOne = 0;
  int leftOne = 0;
  int downOne = 0;
  int upOne = 0;

  int cUp = 0;
  int cDown = 0;
  int cLeft = 0;
  int cRight = 0;

  if (digitalRead(MOD1) == LOW && digitalRead(MOD2) == HIGH)mod1 = 1;
  if (digitalRead(MOD2) == LOW && digitalRead(MOD1) == HIGH)mod2 = 1;

  //SOCD method for left/right is 2ip
  if (digitalRead(LEFT) == LOW && isRight == true)
  {
    pinxAxis = 128-127;
    leftOne = 1;
  }
  else if (digitalRead(RIGHT) == LOW && isLeft == true)
  {
    pinxAxis = 128+127;
    rightOne = 1;
  }

  if (digitalRead(LEFT) == HIGH && digitalRead(RIGHT) == LOW){
    pinxAxis = 128+127;
    rightOne = 1;
    isRight = true;
    isLeft = false;
  }
  if (digitalRead(LEFT) == LOW && digitalRead(RIGHT) == HIGH){
    pinxAxis = 128-127;
    leftOne = 1;
    isLeft = true;
    isRight = false;
  }
  //

  //SOCD method for up/down is neutral
  if (digitalRead(DOWN) == HIGH && digitalRead(UP) == LOW){
    pinyAxis = 128+127;
    upOne = 1;
  }
  if (digitalRead(DOWN) == LOW && digitalRead(UP) == HIGH){
    pinyAxis = 128-127;
    downOne = 1;
  }

  //Reads CStick pins, same logic as controlstick values.
  if (digitalRead(CLEFT) == HIGH && digitalRead(CRIGHT) == LOW){
    pinxAxisC = 255;
    cRight = 1;
  }
  if (digitalRead(CLEFT) == LOW && digitalRead(CRIGHT) == HIGH){
    pinxAxisC = 0;
    cLeft = 1;
  }
  if (digitalRead(CDOWN) == HIGH && digitalRead(CUP) == LOW){
    pinyAxisC = 255;
    cUp = 1;
  }
  if (digitalRead(CDOWN) == LOW && digitalRead(CUP) == HIGH){
    pinyAxisC = 0;
    cDown = 1;
  }

  if (digitalRead(A) == LOW)pinA = 1;
  if (digitalRead(B) == LOW)pinB = 1;
  if (digitalRead(X) == LOW)pinX = 1;
  if (digitalRead(Y) == LOW)pinY = 1;
  if (digitalRead(Z) == LOW)pinZ = 1;
  if (digitalRead(START) == LOW)pinSTART = 1;



  //This is for digital shield.
  //[Crane] Also does a bit of analog shield for Smash4 and Ultimate
  if (digitalRead(R) == LOW) {
    pinR = 1;
    pinRLIGHT = 125;
  }
  if (digitalRead(L) == LOW) {
    pinL = 1;
    pinLLIGHT = 125;
  }

  if (currentGame == Melee)
  {
    if(mod1){
    if(leftOne || rightOne){
      pinxAxis = 128 + ((rightOne - leftOne)*59);
    }
    if(upOne || downOne){
      pinyAxis = 128 + ((upOne - downOne)*52);
    }
    if((leftOne || rightOne) && (upOne || downOne)){
      pinxAxis = 128 + ((rightOne - leftOne)*59);
      pinyAxis = 128 + ((upOne - downOne)*23);
    }
    //Ambiguous DI
    if((leftOne || rightOne) && pinA){
      pinxAxis = 128 + ((rightOne - leftOne)*47);
    }
    //FireFox Angles with cButtons
    if(cUp && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*53);
      pinyAxis = 128 + ((upOne - downOne)*37);
    }
    if(cDown && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*62);
      pinyAxis = 128 + ((upOne - downOne)*30);
    }
    if(cLeft && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*63);
      pinyAxis = 128 + ((upOne - downOne)*37);
    }
    if(cRight && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*51);
      pinyAxis = 128 + ((upOne - downOne)*42);
    }
    //Up and Down Forward Smash
    if((upOne||downOne)&&(cLeft||cRight)){
      pinxAxisC = 128 + ((cRight - cLeft)*127);
      pinyAxisC = 128 + ((upOne - downOne)*41);
    }
  }

  if(mod2){
    if(leftOne || rightOne){
      pinxAxis = 128 + ((rightOne - leftOne)*23);
    }
    if(upOne || downOne){
      pinyAxis = 128 + ((upOne - downOne)*59);
    }
    //Keeps B Reversals Fair
    if((leftOne || rightOne) && pinB){
      pinxAxis = 128 + ((rightOne - leftOne)*59);
    }
    if((leftOne || rightOne) && (upOne || downOne)){
      pinxAxis = 128 + ((rightOne - leftOne)*23);
      pinyAxis = 128 + ((upOne - downOne)*59);
    }

    //Ambiguous DI
    if((leftOne || rightOne) && pinA){
      pinxAxis = 128 + ((rightOne - leftOne)*35);
    }
    //FireFox Angles with cButtons
    if(cUp && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*44);
      pinyAxis = 128 + ((upOne - downOne)*63);
    }
    if(cDown && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*31);
      pinyAxis = 128 + ((upOne - downOne)*64);
    }
    if(cLeft && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*37);
      pinyAxis = 128 + ((upOne - downOne)*63);
    }
    if(cRight && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*47);
      pinyAxis = 128 + ((upOne - downOne)*57);
    }
  }
  }
  else if (currentGame == Ultimate)
  {
  if(mod1){
    if(leftOne || rightOne){
      pinxAxis = 128 + ((rightOne - leftOne)*49);
    }
    if(upOne || downOne){
      pinyAxis = 128 + ((upOne - downOne)*42);
    }
    if((leftOne || rightOne) && (upOne || downOne)){
      pinxAxis = 128 + ((rightOne - leftOne)*80);
      pinyAxis = 128 + ((upOne - downOne)*30);
    }
    //Ambiguous DI
    if((leftOne || rightOne) && pinA){
      pinxAxis = 128 + ((rightOne - leftOne)*47);
    }
    //FireFox Angles with cButtons
    if(cUp && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*53);
      pinyAxis = 128 + ((upOne - downOne)*37);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cDown && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*62);
      pinyAxis = 128 + ((upOne - downOne)*30);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cLeft && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*63);
      pinyAxis = 128 + ((upOne - downOne)*37);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cRight && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*51);
      pinyAxis = 128 + ((upOne - downOne)*42);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    //Up and Down Forward Smash
    if((upOne||downOne)&&(cLeft||cRight)){
      pinxAxisC = 128 + ((cRight - cLeft)*127);
      pinyAxisC = 128 + ((upOne - downOne)*41);
    }
  }

  if(mod2){
    if(leftOne || rightOne){
      pinxAxis = 128 + ((rightOne - leftOne)*33);
    }
    if(upOne || downOne){
      pinyAxis = 128 + ((upOne - downOne)*59);
    }
    //Keeps B Reversals Fair
    if((leftOne || rightOne) && pinB){
      pinxAxis = 128 + ((rightOne - leftOne)*59);
    }
    if((leftOne || rightOne) && (upOne || downOne)){
      pinxAxis = 128 + ((rightOne - leftOne)*30);
      pinyAxis = 128 + ((upOne - downOne)*80);
    }

    //Ambiguous DI
    if((leftOne || rightOne) && pinA){
      pinxAxis = 128 + ((rightOne - leftOne)*35);
    }
    //FireFox Angles with cButtons
    if(cUp && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*44);
      pinyAxis = 128 + ((upOne - downOne)*63);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cDown && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*31);
      pinyAxis = 128 + ((upOne - downOne)*64);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cLeft && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*37);
      pinyAxis = 128 + ((upOne - downOne)*63);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cRight && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*47);
      pinyAxis = 128 + ((upOne - downOne)*57);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
  }
  }
  else if (currentGame == PM)
  {
  if(mod1){
    if(leftOne || rightOne){
      pinxAxis = 128 + ((rightOne - leftOne)*49);
    }
    if(upOne || downOne){
      pinyAxis = 128 + ((upOne - downOne)*65);
    }
    if((leftOne || rightOne) && (upOne || downOne)){
      pinxAxis = 128 + ((rightOne - leftOne)*68);
      pinyAxis = 128 + ((upOne - downOne)*28);
    }
    //Ambiguous DI
    if((leftOne || rightOne) && pinA){
      pinxAxis = 128 + ((rightOne - leftOne)*47);
    }
    //FireFox Angles with cButtons
    if(cUp && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*53);
      pinyAxis = 128 + ((upOne - downOne)*37);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cDown && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*62);
      pinyAxis = 128 + ((upOne - downOne)*30);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cLeft && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*63);
      pinyAxis = 128 + ((upOne - downOne)*37);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cRight && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*51);
      pinyAxis = 128 + ((upOne - downOne)*42);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    //Up and Down Forward Smash
    if((upOne||downOne)&&(cLeft||cRight)){
      pinxAxisC = 128 + ((cRight - cLeft)*127);
      pinyAxisC = 128 + ((upOne - downOne)*41);
    }
  }

  if(mod2){
    if(leftOne || rightOne){
      pinxAxis = 128 + ((rightOne - leftOne)*33);
    }
    if(upOne || downOne){
      pinyAxis = 128 + ((upOne - downOne)*59);
    }
    //Keeps B Reversals Fair
    if((leftOne || rightOne) && pinB){
      pinxAxis = 128 + ((rightOne - leftOne)*59);
    }
    if((leftOne || rightOne) && (upOne || downOne)){
      pinxAxis = 128 + ((rightOne - leftOne)*28);
      pinyAxis = 128 + ((upOne - downOne)*68);
    }

    //Ambiguous DI
    if((leftOne || rightOne) && pinA){
      pinxAxis = 128 + ((rightOne - leftOne)*35);
    }
    //FireFox Angles with cButtons
    if(cUp && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*44);
      pinyAxis = 128 + ((upOne - downOne)*63);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cDown && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*31);
      pinyAxis = 128 + ((upOne - downOne)*64);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cLeft && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*37);
      pinyAxis = 128 + ((upOne - downOne)*63);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
    if(cRight && ((leftOne ||rightOne) && (upOne || downOne))){
      pinxAxis = 128 + ((rightOne - leftOne)*47);
      pinyAxis = 128 + ((upOne - downOne)*57);
      pinxAxisC = 128;
      pinyAxisC = 128;
    }
  }
  }

  //Manual Shield Tilt with R
  if(pinR){
    if(downOne){
      pinyAxis = 128 - 52;
    }
    if(leftOne || rightOne){
      pinxAxis = 128 + ((rightOne - leftOne)*55);
    }
    if((leftOne || rightOne) && downOne){
      pinxAxis = 128 + ((rightOne - leftOne)*55);
      pinyAxis = 128 - 55;
    }
    //Wavedash with R and Mod1
    if(((leftOne || rightOne) && downOne)&& mod1){
      if (currentGame == Melee)
      {
        pinxAxis = 128 + ((rightOne - leftOne)*110);
        pinyAxis = 128 - 65;
      }
      if (currentGame == Ultimate)
      {
        pinxAxis = 128 + ((rightOne - leftOne)*110);
        pinyAxis = 128 - 65;
      }
      if (currentGame == PM)
      {
        pinxAxis = 128 + ((rightOne - leftOne)*123);
        pinyAxis = 128 - 37;
      }
    }
    //Wavedash with R and Mod2
    if(((leftOne || rightOne) && downOne)&& mod2){
      pinxAxis = 128 + ((rightOne - leftOne)*65);
      pinyAxis = 128 - 110;
    }
  }

  if(pinL){
    //Auto Shield Tilt Uses L or Z. Only goes Up
    if(upOne && (leftOne || rightOne)){
      pinxAxis = 128 + ((rightOne - leftOne)*127);
      pinyAxis = 128 + 112;
    }

    //Axe Method Shield Drop
    if (currentGame == Melee)
    {
      if(downOne && (leftOne || rightOne)){
        pinxAxis = 128 + ((rightOne - leftOne)*96);
        pinyAxis = 128 - 91;
      }
    }
    else
    {
      if(downOne && (leftOne || rightOne)){
        pinxAxis = 128 + ((rightOne - leftOne)*96);
        pinyAxis = 128 - 99;
      }
    }
    if(mod1){
      pinLLIGHT = 74;
      pinL = 0;
    }
    if(mod2){
      pinLLIGHT = 171;
      pinL = 0;
    }
  }

  if(pinZ){
    if(upOne && (leftOne || rightOne)){
      pinxAxis = 128 + ((rightOne - leftOne)*127);
      pinyAxis = 128 + 112;
    }
  }



  //D-Pad
 if(digitalRead(MOD1)==LOW && digitalRead(MOD2)==LOW){
        pinxAxisC = 128;
        pinyAxisC = 128;
      if(digitalRead(CRIGHT)==HIGH && digitalRead(CLEFT)==LOW){
          pinDLEFT=1;
      }
      else if(digitalRead(CUP)==HIGH && digitalRead(CDOWN)==LOW){
          pinDDOWN=1;
      }
      else if(digitalRead(CDOWN)==HIGH  && digitalRead(CUP)==LOW){
         pinDUP=1;
      }
      else if(digitalRead(CLEFT)==HIGH  && digitalRead(CRIGHT)==LOW){
         pinDRIGHT=1;
      }
  }



  //reports data
  d.report.a = pinA;
  d.report.b = pinB;
  d.report.x = pinX;
  d.report.y = pinY;
  d.report.z = pinZ;
  d.report.start = pinSTART;
  d.report.r = pinR;
  d.report.l = pinL;
  d.report.left = pinLLIGHT;
  d.report.right = pinRLIGHT;
  d.report.xAxis = pinxAxis;
  d.report.yAxis = pinyAxis;
  d.report.cxAxis = pinxAxisC;
  d.report.cyAxis = pinyAxisC;
  d.report.dup = pinDUP;
  d.report.dright = pinDRIGHT;
  d.report.ddown = pinDDOWN;
  d.report.dleft = pinDLEFT;
  //sends the complied data to console when console polls for the input
  GamecubeConsole.write(d);

}
