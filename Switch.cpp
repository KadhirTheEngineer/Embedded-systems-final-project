/*
 * Switch.cpp
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
    // write this
    //RIGHT
    IOMUX->SECCFG.PINCM[PA9INDEX]  = 0x00040081;
    IOMUX->SECCFG.PINCM[PA17INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PA31INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PA28INDEX] = 0x00040081;

    //LEFT
    IOMUX->SECCFG.PINCM[PA25INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PA26INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PB13INDEX] = 0x00040081;
    IOMUX->SECCFG.PINCM[PA24INDEX] = 0x00040081;
  
}
// return current state of switches
uint32_t Switch_In(void){
    // write this
    uint32_t RUP    = ((GPIOA->DIN31_0 & (1<<28))>>28);
    uint32_t RRIGHT = ((GPIOA->DIN31_0 & (1<<9))>>8);
    uint32_t RDOWN  = ((GPIOA->DIN31_0 & (1<<17))>>15);
    uint32_t RLEFT  = ((GPIOA->DIN31_0 & (1<<31))>>28);

    uint32_t LUP    = ((GPIOA->DIN31_0 & (1<<24))>>20);
    uint32_t LRIGHT = ((GPIOA->DIN31_0 & (1<<25))>>20);
    uint32_t LDOWN  = ((GPIOA->DIN31_0 & (1<<26))>>20);
    uint32_t LLEFT  = ((GPIOB->DIN31_0 & (1<<13))>>6);

    return (RUP|RRIGHT|RDOWN|RLEFT|LUP|LRIGHT|LDOWN|LLEFT); //replace this your code

    //0-7 bits lleft, ldown, lright, lup, rleft, rdown, rright, rup;
}
