#if defined(STM32_F100RB)
  #include <stm32f10x.h>
#elif defined(STM32_F407VG)
  #include <stm32f4xx.h>
#endif

//global variables
//for testing purposes
typedef enum {false, true} bool;
bool button = true;
uint32_t button_value = 1;
int i2 = 0;
uint32_t counter = 0;

void delay(void) {
  int i = 400000; /* About 1/4 second delay */

  while (i-- > 0)
    asm("nop");
}

int main(void) {

/*
ERROR:
GNU MCU Eclipse OpenOCD, 64-bitOpen On-Chip Debugger 0.10.0+dev-00593-g23ad80df4 (2019-04-23-00:01)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html

Error: init mode failed (unable to connect to the target)
in procedure 'program'
** OpenOCD init failed **
shutdown command invoked

*** [upload] Error 1
This occurs because of driver error:

Wisdom on the internet has it that this happens if you reconfigure
the SWD pins such that they no longer work
for the debug interface. If I’m not mistaken, they are all on port A. SWDIO is PA13, SWCLK is PA14
*/

  #if defined(STM32_F100RB)
    //Enable the clocks for GPIOC and GPIOA 0x10
    /* Enable the GPIOA [PA0 is the button] (bit 2) and GPIOC [PC8 (blue LED)] (bit 4) */
    /* See 7.3.7 in stm32f100x reference manual of RM0008*/
    RCC ->APB2ENR |= (0x04 | 0x10);
  #elif defined(STM32_F407VG)
    //Enable clocks for GPIOD for Pin 15 & Pin 12 for the blue LED & Green LED; and GPIOA Pin 0 for User button
    //blue LED is a user LED connected to PD15 of the STM32F407VGT6 on STM32F4 Discovery board.
    //Green LED is a user LED connected to the PD12 of the STM32F407VGT6 on STM32F4 Discovery board.
    //user button is on PA0 PIN of the STM32F407VG on STM32F4 Discovery board.
    // See 6.3.10 in STM32F407x reference manual of RM0090
    // Enable the GPIOA (bit 0) and GPIOD (bit 3)
    RCC ->AHB1ENR |= (RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN);
  #endif

  #if defined(STM32_F100RB)
    //Configure the Button
    /* Set GPIOA Pin 0 to input floating */
    /* 9.2.1 in stm32f100x reference manual of RM0008*/
    GPIOA ->CRL |= 0x04;
  #elif defined(STM32_F407VG)
    //Configure the user Button on PA0 for STM32F407VGT6 on STM32F4 Discovery board.
    // See table 35 in section 8.3 and see section 8.4.1 in STM32F407x reference manual of RM0090
    // I/O configuartion = Input Floating; MODER=00; OTYPER=N/A; OSPEEDR=N/A; PUPDR=00;
    // [bit 1, bit 0] for Pin 0 must be set to 0,0 for Input. We need only two bits out of 32 bits
    // Important Note:
    // Watch out that you do not disable the SWDIO is PA13, SWCLK is PA14
    GPIOA ->MODER |= (GPIO_MODER_MODER0-GPIO_MODER_MODER0);
    // See table 35 in  section 8.3 and see section 8.4.4 in STM32F407x reference manual of RM0090
    // [bit 1, bit 0 = 1, 0] Input PD (Table 35: Pull down)
    // Important Note:
    // Watch out that you do not disable the SWDIO is PA13, SWCLK is PA14
    GPIOA ->PUPDR |= (GPIO_PUPDR_PUPDR0_1);
  #endif

  #if defined(STM32_F100RB)
    //Configure the Blue LED
    /* Set GPIOC Pin 8 as outputs at 2Mhz speed */
    /* 9.2.2 in stm32f100x reference manual of RM0008*/
    GPIOC ->CRH |= 0x02;
  #elif defined(STM32_F407VG)
    //Configure the Blue LED, PD15, for STM32F407VGT6 on STM32F4 Discovery board.
    // See table 35 in section 8.3 and see section 8.4.1 in STM32F407x reference manual of RM0090
    // I/O configuration = GP output, PP: MODER=01; OTYPER=0; OSPEEDR=(01: Medium speed); PUPDR=00; for PIN 15 on GPIOD
    GPIOD ->MODER |= (GPIO_MODER_MODER15_0);
    GPIOD ->OTYPER |= (GPIO_OTYPER_OT_15-GPIO_OTYPER_OT_15);
    GPIOD ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_0;
    GPIOD ->PUPDR |= (GPIO_PUPDR_PUPDR15-GPIO_PUPDR_PUPDR15);
  #endif

  #if defined(STM32_F100RB)
    //Configure the Green LED
    /* Set GPIOC Pin 9 as outputs at 2Mhz speed */
    /* 9.2.2 in stm32f100x reference manual of RM0008*/
    GPIOC ->CRH |= 0x20;
  #elif defined(STM32_F407VG)
    //Configue the Green LED, PD12, for STM32F407VGT6 on STM32F4 Discovery board.
    // See table 35 in section 8.3 and see section 8.4.1 in STM32F407x reference manual of RM0090
    // I/O configuration = GP output, PP: MODER=01; OTYPER=0; OSPEEDR=(01: Medium speed); PUPDR=00; for PIN 12 on GPIOD
    GPIOD ->MODER |= (GPIO_MODER_MODER12_0);
    GPIOD ->OTYPER |= (GPIO_OTYPER_OT_12-GPIO_OTYPER_OT_12);
    GPIOD ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_0;
    GPIOD ->PUPDR |= (GPIO_PUPDR_PUPDR12-GPIO_PUPDR_PUPDR12);
  #endif

  while (1) {
    delay();

    //this is a test this is only a test

    #if defined(STM32_F100RB)
      /* see 9.2.3 in stm32f100x reference manual of RM0008*/
      // Read the button - the button pulls down PA0 to logic 0
      //(button circuit is active low) so change the logic
      //when the button is pressed the button_value will be equal to 0
      //otherwise button_value = 1
      button_value = (GPIOA ->IDR & 0x1);
    #elif defined(STM32_F407VG)
      //See section 8.4.5 in STM32F407x reference manual of RM0090
      // Read the button - the button pulls down PA0 to logic 0
      //(button circuit is active low)
      button_value = ((GPIOA ->IDR) & GPIO_IDR_IDR_0);
    #endif

    counter++;
    if (button_value == 1) {
      //button_value is equal to 1 when the button is pressed
      button = false;
      #if defined(STM32_F100RB)
        /* see 9.2.5 in stm32f100x reference manual of RM0008*/
        //turn off the Blue light, PC8 is the blue LED
        GPIOC ->BSRR = 1 << 24;
        //turn on the Green light, PC9 is the green LED
        GPIOC ->BSRR = 1 << 9;
      #elif defined(STM32_F407VG)
        //turn off the Blue Light, PD15
        //turn on the Green Light, PD12
        //see section 8.4.7 in in STM32F407x reference manual of RM0090
        GPIOD ->BSRRH |= GPIO_BSRR_BS_15; //reset register
        GPIOD ->BSRRL |= GPIO_BSRR_BS_12; //set register
      #endif

    }
    else {
      //button_value is equal to 0 when the button is NOT pressed
      button = true;
      #if defined(STM32_F100RB)
        //  turn ON the light, PC8 is the blue LED
        /* see 9.2.5 in stm32f100x reference manual of RM0008*/
        //turn on the Blue light, PC8
        GPIOC ->BSRR = 1 << 8;
       //turn off the Green light, PC9
        GPIOC ->BSRR = 1 << 25;
      #elif defined(STM32_F407VG)
        //turn ON Blue Light, PD15
        //turn Off Green Light, PD12
        //see section 8.4.7 in in STM32F407x reference manual of RM0090
        GPIOD ->BSRRL |= GPIO_BSRR_BS_15;  //set register
        GPIOD ->BSRRH |= GPIO_BSRR_BS_12;  //reset register
      #endif

      //break point for testing purposes
      asm("nop");
    }
    asm("nop");
  }
}
