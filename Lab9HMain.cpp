// Lab9HMain.cpp
// Runs on MSPM0G3507
// Lab 9 ECE319H
// Your name
// Last Modified: 1/1/2024

#include <stdio.h>
#include <stdint.h>
#include <cmath>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);
extern "C" void TIMG0_IRQHandler(void);

#define ONEW 16
#define ONEH 20



#define BORD5 5
#define BORD10 10

#define XMIN 2
#define XMAX 126
#define YMIN 22
#define YMAX 158

/*
   * 1. 8,23
   * 2. 61, 24
   * 3. 9, 90
   * 4. 61, 91
   *    52,66
 */

// POSITIIONS FOR SELECTION BOX.
#define P1SELX 10
#define P1SELY 24
#define P2SELX 63
#define P2SELY 24
#define P3SELX 10
#define P3SELY 90
#define P4SELX 63
#define P4SELY 90
#define SELWIDTH 52
#define SELHEIGHT 66

// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}

//global variables

SlidePot Sensor(1200,0); // needs calibration //first joystick
SlidePot Sensor0(1200,0); // needs calibration // second joystick

uint32_t data1P1;        // 12-bit ADC
uint32_t data2P1;        // 12-bit ADC

uint8_t lang = 0;

uint32_t data1P2;        // 12-bit ADC
uint32_t data2P2;        // 12-bit ADC

uint32_t selectxp1;
uint32_t selectyp1;
uint32_t selectxp2;
uint32_t selectyp2;


int32_t globXP1 = 42;
int32_t globYP1 = 42;

int32_t globXP2 = 82;
int32_t globYP2 = 82;

int32_t XC1;
int32_t YC1;
int32_t XC2;
int32_t YC2;

int32_t switchesstart = 1;

int32_t COLDIST;
int32_t healthp1 = 60;
int32_t healthp2 = 60;

uint32_t Position1P1;
uint32_t Position2P1; // 32-bit fixed-point 0.001 cm

uint32_t Position1P2;
uint32_t Position2P2;

uint8_t collisionflag = 0;
uint8_t Playerselectflag = 0;

float FloatPosition;  // 32-bit floating-point cm
uint32_t startTime,stopTime;
uint32_t Offset,ADCtime,Converttime,FloatConverttime,OutFixtime,FloatOutFixtime; // in bus cycles
uint32_t Time;

uint8_t gamestartflag = 0;

uint32_t testswitch;

void attack(void){
    switchesstart = Switch_In();
    //while(((switchesstart & (1)) != (1)) && ((switchesstart & (1<<4)) != (1<<4)) && (switchesstart & (1 << 3)) != (1<<3) && (switchesstart & (1<<7)) != (1<<7)){
       // switchesstart = Switch_In();
    //}
    if(((switchesstart & (1)) == (1))) { //left player kick
        Sound_Kick();
        //flash red player kick icon
        healthp1-=2;
        //decrement hp
        }
    else if ((switchesstart&(1 << 5)) == (1 <<5)) //right player kick
        {
        Sound_Kick();
        healthp2-= 2;
        //flash blue player kick icon
        //decrement hp
        }
    else if ((switchesstart & (1<<3)) == (1<<3)){ //left player punch
        Sound_Punch();
        healthp1 -= 1;
        //flash red player punch icon
        //decrement hp
    }
    else if ((switchesstart & (1 << 7)) == (1<<7)){
        Sound_Punch(); //left player punch
        healthp2-=1;
        //flash blue player punch icon
        //decrement hp
    }
    else{
        return;
    }
}
//0-7 bits lleft, ldown, lright, lup, rleft, rdown, rright, rup;

// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // set the semaphore
       Sensor.ADC_InDual(&data1P1, &data2P1);
       Sensor.ADC0_InDual(&data1P2, &data2P2);
       //ST7735_InitPrintf();

       if(COLDIST<20) {
           collisionflag = 1;
           //health++;
       }else{
           collisionflag = 0;
       }

       if(collisionflag && gamestartflag) attack();

       if(healthp1 <= 0){
           gamestartflag = 0;
           ST7735_FillScreen(ST7735_BLACK);
           if (lang == 0){
           ST7735_SetCursor(1, 1);
           printf("BLUE WINS");
           ST7735_SetCursor(1, 2);
           printf("%s %d", "REMAINING HP", healthp2);
           }
           else{
               ST7735_SetCursor(1, 1);
               printf("EL AZUL GANA");
               ST7735_SetCursor(1, 2);
               printf("%s %d", "SALUD RESTANTE", healthp2);
           }
           while(1);
           //P2 WINS
       }
       else if(healthp2 <= 0){
           gamestartflag = 0;
           //ST7735_FillScreen(ST7735_WHITE);
           ST7735_FillScreen(ST7735_BLACK);
           if (lang == 0){
           ST7735_SetCursor(1, 1);
           printf("RED WINS");
           ST7735_SetCursor(1, 2);
           printf("%s %d", "REMAINING HP", healthp1);
           }
           else{
               ST7735_SetCursor(1, 1);
               printf("EL RED GANA");
               ST7735_SetCursor(1, 2);
               printf("%s %d", "SALUD RESTANTE", healthp1);
           }
           while(1);
           //P1 WINS
       }

    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(int myPhrase=0; myPhrase<= 2; myPhrase++){
    for(int myL=0; myL<= 3; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
 /* ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);
*/
  for(uint32_t t=500;t>0;t=t-5){
    SmallFont_OutVertical(t,104,6); // top left
    Clock_Delay1ms(50);              // delay 50 msec
  }
  ST7735_FillScreen(0x0000);   // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString((char *)"GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString((char *)"Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString((char *)"Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while(1){
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Switch_Init();
  while(1){
    // write code to test switches and LEDs
      testswitch = Switch_In();
   
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  TimerG12_IntArm(80000000/0.5,2);
  __enable_irq();
 while(1){
    /*now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }*/
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN

/*void TIMG0_IRQHandler(void){
  if((TIMG0->CPU_INT.IIDX) == 1 && Playerselectflag){ // this will acknowledge
      Sensor.ADC_InDual(&data1P1, &data2P1);
      Sensor.ADC0_InDual(&data1P2, &data2P2);

      Position1P1 = Sensor.Convert(data1P1);
       Position2P1 = Sensor.Convert(data2P1);

       Position1P2 = Sensor.Convert(data1P2);
       Position2P2 = Sensor.Convert(data2P2);

       //BORDER COLLISION
       Position1P1 /= 1500;
       Position2P1 /= 200;
//       Position1P2 /= 200;
//       Position2P2 /= 200;

  }
}
*/

void startingscreen(void){
    ST7735_DrawBitmap(0, 160, start, 128, 160);
    switchesstart = Switch_In();
    while(((switchesstart & (1)) != (1)) && ((switchesstart & (1<<4)) != (1<<4))){
        switchesstart = Switch_In();
    }
    if(((switchesstart & (1)) == (1))) {lang = 0;}
    else{lang = 1;}
    for(int shittypoopoo = 0; shittypoopoo < 160; shittypoopoo++){
        ST7735_FillRect(0, 0, 128, shittypoopoo, ST7735_Color565(255, 255, 255));
    }


}


int8_t peeP1= 0;
int8_t pooP1= 0;

int8_t peeP2= 0;
int8_t pooP2= 0;
uint8_t selectedplayernump1 = 0;
uint8_t selectedplayernump2 = 0;


void selectplayer(void){
  Playerselectflag = 1;
  //TimerG0_IntArm(1000000,40,0);
  ST7735_DrawBitmap(0, 160, englishplayerselect, 128, 160);
  if(lang) ST7735_DrawBitmap(12, 22, spanish, 108, 9);

  switchesstart = Switch_In();
  while(((switchesstart & (1<<7)) != (1<<7)) || ((switchesstart & (1<<3)) != (1<<3))){

  Position1P1 = Sensor.Convert(data1P1);
  Position2P1 = Sensor.Convert(data2P1);

  Position1P2 = Sensor.Convert(data1P2);
  Position2P2 = Sensor.Convert(data2P2);

  //if(){}
  Position1P1 /= 200;
  Position2P1 /= 200;
  Position1P1++;
  Position2P1++;
  peeP1 = 1-(Position2P1-5); //goofy math to account for stick drift
  pooP1 = (Position1P1-5);

  Position1P2 /= 200;
  Position2P2 /= 200;
  Position1P2++;
  Position2P2++;
  peeP2 = 1-(Position2P2-5); //goofy math to account for stick drift
  pooP2 = (Position1P2-5);

  if(peeP1 == -4 && pooP1 == 0) selectedplayernump1=0;
  if(peeP1 == 0 && pooP1 == 5) selectedplayernump1=1;
  if(peeP1 == 5 && pooP1 == 0) selectedplayernump1=2;
  if(peeP1 == 0 && pooP1 == -4) selectedplayernump1=3;


              if(peeP2 == -4 && pooP2 == 0) selectedplayernump2=0;
              if(peeP2 == 0 && pooP2 == 5) selectedplayernump2=1;
              if(peeP2 == 5 && pooP2 == 0) selectedplayernump2=2;
              if(peeP2 == 0 && pooP2 == -4) selectedplayernump2=3;

              ST7735_FillRect(P1SELX, P1SELY, 2, SELHEIGHT, (selectedplayernump1 == 0)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 0)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P1SELX, P1SELY, SELWIDTH, 2, (selectedplayernump1 == 0)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 0)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P1SELX+SELWIDTH-2, P1SELY, 2, SELHEIGHT, (selectedplayernump1 == 0)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 0)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P1SELX, P1SELY+SELHEIGHT-2, SELWIDTH, 2, (selectedplayernump1 == 0)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 0)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P2SELX, P2SELY, 2, SELHEIGHT, (selectedplayernump1 == 1)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 1)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P2SELX, P2SELY, SELWIDTH, 2, (selectedplayernump1 == 1)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 1)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P2SELX+SELWIDTH-2, P2SELY, 2, SELHEIGHT, (selectedplayernump1 == 1)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 1)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P2SELX, P2SELY+SELHEIGHT-2, SELWIDTH, 2, (selectedplayernump1 == 1)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 1)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P3SELX, P3SELY, 2, SELHEIGHT, (selectedplayernump1 == 2)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 2)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P3SELX, P3SELY, SELWIDTH, 2, (selectedplayernump1 == 2)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 2)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P3SELX+SELWIDTH-2, P3SELY, 2, SELHEIGHT, (selectedplayernump1 == 2)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 2)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P3SELX, P3SELY+SELHEIGHT-2, SELWIDTH, 2, (selectedplayernump1 == 2)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 2)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P4SELX, P4SELY, 2, SELHEIGHT, (selectedplayernump1 == 3)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 3)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P4SELX, P4SELY, SELWIDTH, 2, (selectedplayernump1 == 3)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 3)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P4SELX+SELWIDTH-2, P4SELY, 2, SELHEIGHT, (selectedplayernump1 == 3)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 3)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));
               ST7735_FillRect(P4SELX, P4SELY+SELHEIGHT-2, SELWIDTH, 2, (selectedplayernump1 == 3)?ST7735_Color565(255, 0, 0):(selectedplayernump2 == 3)?ST7735_Color565(0, 0, 255):ST7735_Color565(255, 255, 255));

               switchesstart = Switch_In();

  }


  }




  //PLAYER BOX WIDTHS
  /*
   * 1. 8,23
   * 2. 61, 24
   * 3. 9, 90
   * 4. 61, 91
   *    52,66
   * */

int main(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  Switch_Init(); // initialize switches
  Sound_Init();  // initialize sound

  __enable_irq();



  //joystick init
  Sensor.ADC_InitDual(3, 4, 0); //PB18 = ADC1 channel 5, slidepot
  Sensor0.ADC0_InitDual(5, 0, 0); //PB18 = ADC1 channel 5, slidepot

  TimerG12_IntArm(80000000/30,2);


  startingscreen();
  selectplayer();
  gamestartflag = 1;
  COLDIST = 100;
  ST7735_FillScreen(ST7735_BLACK);



    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  //ST7735_DrawBitmap(0, 160, playerselect, 128, 160);

  ST7735_FillRect(0, 20, 2, 160, ST7735_Color565(255, 0, 0));
   ST7735_FillRect(0, 20, 128, 2, ST7735_Color565(255, 0, 0));
   ST7735_FillRect(126, 20, 2, 160, ST7735_Color565(255, 0, 0));
   ST7735_FillRect(0, 158, 128, 2, ST7735_Color565(255, 0, 0));




  //Sensor.Init(); // PB18 = ADC1 channel 5, slidepot
  //LED_Init();    // initialize LED
  //TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  // initialize all data structures

  while(1){
      // complete this
        // wait for semaphore using a call to a method in Sensor
         Sensor.Sync();
        //TIMG12_IRQHandler();
        GPIOB->DOUTTGL31_0 = RED; // toggle PB26 (minimally intrusive debugging)

        //GPIOB->DOUTTGL31_0 = RED; // toggle PB26 (minimally intrusive debugging)
        //GPIOB->DOUTTGL31_0 = RED; // toggle PB26 (minimally intrusive debugging)

        Position1P1 = Sensor.Convert(data1P1);
        Position2P1 = Sensor.Convert(data2P1);

        Position1P2 = Sensor.Convert(data1P2);
        Position2P2 = Sensor.Convert(data2P2);

        //ST7735_SetCursor(1,1); // second row
        // display distance in top row OutFix
        //OutFix(Position1);
        //ST7735_DrawBitmap(168, 0, screen, 120, 168);


        Time++;
        //BORDER COLLISION
        Position1P1 /= 200;
        Position2P1 /= 200;
        Position1P1++;
        Position2P1++;
        globXP1 += 1-(Position2P1-5); //goofy math to account for stick drift
        if(globXP1<XMIN) globXP1 = XMIN;
        if(globXP1+BORD5+BORD5+ONEW>XMAX) globXP1 = XMAX-(BORD5+BORD5+ONEW);
        globYP1 -= (Position1P1-5);
        if(globYP1<=YMIN) globYP1 = YMIN;
        if(globYP1+BORD5+BORD5+ONEH>YMAX) globYP1 = YMAX-(BORD5+BORD5+ONEH);

        Position1P2 /= 200;
        Position2P2 /= 200;
        Position1P2++;
        Position2P2++;
        globXP2 -= (Position2P2-5);
        if(globXP2<XMIN) globXP2 = XMIN;
        if(globXP2+BORD5+BORD5+ONEW>XMAX) globXP2 = XMAX-(BORD5+BORD5+ONEW);
        globYP2 -= (Position1P2-5);
        if(globYP2<=YMIN) globYP2 = YMIN;
        if(globYP2+BORD5+BORD5+ONEH>YMAX) globYP2 = YMAX-(BORD5+BORD5+ONEH);

        //SPRITE COLLISION
        XC1 = globXP1+(BORD5+BORD5+ONEW)/2;
        YC1 = globYP1+(BORD5+BORD5+ONEH)/2;

        XC2 = globXP2+(BORD5+BORD5+ONEW)/2;
        YC2 = globYP2+(BORD5+BORD5+ONEH)/2;

        COLDIST = (uint32_t)std::sqrt((double) ((XC1-XC2)*(XC1-XC2) + (YC1-YC2)*(YC1-YC2)) ); // under 22 means collision


        //healthbars
        //health = (health>56)?56:health;
        ST7735_FillRect(0, 0, 60, 20, ST7735_Color565(255, 255, 255));
        ST7735_FillRect(2, 2, healthp1-4, 16, ST7735_Color565(0, 255, 0));
        ST7735_FillRect(healthp1+2, 2, 58-healthp1, 18, ST7735_Color565(255, 255, 255));

        ST7735_FillRect(68, 0, 60, 20, ST7735_Color565(255, 255, 255));
        ST7735_FillRect(70, 2, healthp2-4, 16, ST7735_Color565(0, 255, 0));
        ST7735_FillRect(70+healthp2+2, 2, 128-healthp2, 18, ST7735_Color565(255, 255, 255));



        //sprites and borders
        ST7735_DrawBitmap(globXP1+BORD5, globYP1+BORD5+ONEH, players[selectedplayernump1], ONEW, ONEH);
        ST7735_FillRect(globXP1, globYP1, BORD5, BORD5+BORD5+ONEH, ST7735_Color565(0, 0, 0));
        ST7735_FillRect(globXP1+BORD5, globYP1, ONEW, BORD5, ST7735_Color565(0, 0, 0));
        ST7735_FillRect(globXP1+BORD5+ONEW, globYP1, BORD5, BORD5+BORD5+ONEH, ST7735_Color565(0, 0, 0));
        ST7735_FillRect(globXP1+BORD5, globYP1+BORD5+ONEH, ONEW, BORD5, ST7735_Color565(0, 0, 0));


        ST7735_DrawBitmap(globXP2+BORD5, globYP2+BORD5+ONEH, players[selectedplayernump2], ONEW, ONEH);
        ST7735_FillRect(globXP2, globYP2, BORD5, BORD5+BORD5+ONEH, ST7735_Color565(0, 0, 0));
        ST7735_FillRect(globXP2+BORD5, globYP2, ONEW, BORD5, ST7735_Color565(0, 0, 0));
        ST7735_FillRect(globXP2+BORD5+ONEW, globYP2, BORD5, BORD5+BORD5+ONEH, ST7735_Color565(0, 0, 0));
        ST7735_FillRect(globXP2+BORD5, globYP2+BORD5+ONEH, ONEW, BORD5, ST7735_Color565(0, 0, 0));

  }
}
