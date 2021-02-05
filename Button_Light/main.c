#include "stm32f10x.h"

//global variables
//for testing purposes
int button = 0;

void delay(void) {
  int i = 100000; /* About 1/4 second delay */

  while (i-- > 0)
    asm("nop");
}

int main(void) {

  //Enable the clocks for GPIOC and GPIOA 0x10
  /* Enable the GPIOA [PA0 is the button] (bit 2) and GPIOC [PC8 (blue LED)] (bit 4) */
  /* See 7.3.7 in stm32f100x reference manual of RM0008*/
  RCC ->APB2ENR |= 0x04 | 0x10;

  //Configure the Button
  /* Set GPIOA Pin 0 to input floating */
  /* 9.2.1 in stm32f100x reference manual of RM0008*/
  GPIOA ->CRL = 0x04;

  //Configure the LED
  /* Set GPIOC Pin 8 as outputs at 2Mhz speed */
  /* 9.2.2 in stm32f100x reference manual of RM0008*/
  GPIOC ->CRH = 0x02;

  while (1) {
    delay();

    //this is a test this is only a test

    /* see 9.2.3 in stm32f100x reference manual of RM0008*/
    // Read the button - the button pulls down PA0 to logic 0
    //button = ((GPIOA ->IDR & 0x1) == 0);

    if (((GPIOA ->IDR & 0x1) == 0)) {
      // (button circuit is active low) (since active low, then reset the bit to turn ON the light)
      /* see 9.2.5 in stm32f100x reference manual of RM0008*/
      //LED on PC8
      GPIOC ->BSRR = 1 << 24;
    }
    else {
      /* see 9.2.5 in stm32f100x reference manual of RM0008*/
      //LED off PC8 (since circuit is active low, set the bit to turn off the light)
      GPIOC ->BSRR = 1 << 8;
    }
  }
}
