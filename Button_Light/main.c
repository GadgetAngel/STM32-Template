#include "stm32f10x.h"

//global variables
//for testing purposes
typedef enum {false, true} bool;
bool button = true;
uint16_t button_value = -1;
int i = 0;
uint32_t counter = 0;

void delay(void) {
  i = 100000; /* About 1/4 second delay */

  while (i-- > 0)
    asm("nop");
}

void do_nothing (void) {
  return;
}

int main(void) {

  //Enable the clocks for GPIOC and GPIOA 0x10
  /* Enable the GPIOA [PA0 is the button] (bit 2) and GPIOC [PC8 (blue LED)] (bit 4) */
  /* See 7.3.7 in stm32f100x reference manual of RM0008*/
  RCC ->APB2ENR |= (0x04 | 0x10);

  //Configure the Button
  /* Set GPIOA Pin 0 to input floating */
  /* 9.2.1 in stm32f100x reference manual of RM0008*/
  GPIOA ->CRL = 0x04;

  //Configure the Blue LED
  /* Set GPIOC Pin 8 as outputs at 2Mhz speed */
  /* 9.2.2 in stm32f100x reference manual of RM0008*/
  GPIOC ->CRH = 0x02;

  //Configure the Green LED
  /* Set GPIOC Pin 9 as outputs at 2Mhz speed */
  /* 9.2.2 in stm32f100x reference manual of RM0008*/
  GPIOC ->CRH |= 0x20;

  while (1) {
    delay();

    //this is a test this is only a test

    /* see 9.2.3 in stm32f100x reference manual of RM0008*/
    // Read the button - the button pulls down PA0 to logic 0
    //(button circuit is active low) so change the logic
    //when the button is pressed the if statement will evaluate to true
    button_value = (GPIOA ->IDR & 0x1);
    counter++;
    if (button_value == 0) {
      button = false;  //when the button is not pressed this will be false
      /* see 9.2.5 in stm32f100x reference manual of RM0008*/
      //turn off the Blue light, PC8 is the blue LED
      GPIOC ->BSRR = 1 << 24;
      //turn on the Green light, PC9 is the green LED
      GPIOC ->BSRR = 1 << 9;
    }
    else {
      button = true;  //when the button is pressed this will be true
      //  turn ON the light, PC8 is the blue LED
      /* see 9.2.5 in stm32f100x reference manual of RM0008*/
      //turn on the Blue light, PC8
      GPIOC ->BSRR = 1 << 8;
      //turn off the Green light, PC9
      GPIOC ->BSRR = 1 << 25;
      do_nothing();
    }
  }
}
