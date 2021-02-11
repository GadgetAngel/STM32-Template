#if defined(STM32_F100RB)
  #include <stm32f10x.h>
#elif defined(STM32_F407VG)
  #include <stm32f4xx.h>
#elif defined (STM32L433xx)
  #include <STM32L433xx.h>
#endif

#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK_ALL(x,y) (!(~(x) & (y)))
#define BITMASK_CHECK(x,y) (((x) & (y)) == (y))
#define BITMASK_CHECK_ANY(x,y) ((x) & (y))

//global variables
//for testing purposes
int n = 0;
int inc_const = 1;
uint32_t button;

void delay(void) {
  int32_t i = 80000; /* About 1 second delay */

  while (i-- > 0)
    asm("nop");
}

void inc(void){
  n += inc_const;
}

int main(void) {

  #if defined(STM32_F100RB)
    /* Enable the GPIOA (bit 2) and GPIOC (bit 4) */
    /* See 6.3.7 in stm32f100x reference manual */
    RCC ->APB2ENR |= 0x10 | 0x04;
  #elif defined(STM32_F407VG)
    //Enable clocks for GPIOD for Pin 15 & Pin 12 for the blue LED & Green LED; and GPIOA Pin 0 for User button
    //blue LED is a user LED connected to PD15 of the STM32F407VGT6 on STM32F4 Discovery board.
    //Green LED is a user LED connected to the PD12 of the STM32F407VGT6 on STM32F4 Discovery board.
    //user button is on PA0 PIN of the STM32F407VG on STM32F4 Discovery board.
    // See 6.3.10 in STM32F407x reference manual of RM0090
    // Enable the GPIOA (bit 0) and GPIOD (bit 3)
    RCC ->AHB1ENR |= (RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN);
  #elif defined(STM32L433xx)
    //User Button is on PC13
    //User LED is on  PB13.
    // SWDIO & SWCLK pins for the board: PA13 is SWDIO & PA14 is SWCLK (do not disable these two pins)
    // enable clocks on Port A for SWDIO/SWCLK pins; Enable Port B for LED; Enable Port C for User button
    RCC -> AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN |RCC_AHB2ENR_GPIOBEN);
  #endif

  #if defined(STM32_F100RB)
    /* Set GPIOA Pin 0 to input floating */
    /* 7.2.1 in stm32f100x reference manual */
    GPIOA ->CRL = 0x04;
  #elif defined(STM32_F407VG)
    //Configure the user Button on PA0 for STM32F407VGT6 on STM32F4 Discovery board.
    // See table 35 in section 8.3 and see section 8.4.1 in STM32F407x reference manual of RM0090
    // I/O configuartion = Input Floating; MODER=00; OTYPER=N/A; OSPEEDR=N/A; PUPDR=00;
    // [bit 1, bit 0] for Pin 0 must be set to 0,0 for Input. We need only two bits out of 32 bits
    // Important Note:
    // Watch out that you do not disable the SWDIO is PA13, SWCLK is PA14
    GPIOA ->MODER &= ~GPIO_MODER_MODER0;
    // See table 35 in  section 8.3 and see section 8.4.4 in STM32F407x reference manual of RM0090
    // [bit 1, bit 0 = 1, 0] Input PD (Table 35: Pull down)
    // Important Note:
    // Watch out that you do not disable the SWDIO is PA13, SWCLK is PA14
    GPIOA ->PUPDR |= GPIO_PUPDR_PUPDR0_1;
  #elif defined(STM32L433xx)
    //Configure the User button on PC13 for the nucleo_l433rc_p board
    // PC13 as Input mode
    BITMASK_CLEAR(GPIOC ->MODER, GPIO_MODER_MODE13);
    //GPIOC ->MODER &= ~GPIO_MODER_MODE13;
    //
    //PC 13 as PULL down
    BITMASK_SET(GPIOC -> PUPDR, GPIO_PUPDR_PUPD13_1);
    //GPIOC -> PUPDR |= GPIO_PUPDR_PUPD13_1;
  #endif

  #if defined(STM32_F100RB)
    /* Set GPIOC Pin 8 and Pin 9 to outputs */
    /* 7.2.2 in stm32f100x reference manual */
    GPIOC ->CRH = 0x11;
  #elif defined(STM32_F407VG)
    //Configure the Blue LED, PD15, for STM32F407VGT6 on STM32F4 Discovery board.
    // See table 35 in section 8.3 and see section 8.4.1 in STM32F407x reference manual of RM0090
    // I/O configuration = GP output, PP: MODER=01; OTYPER=0; OSPEEDR=(01: Medium speed); PUPDR=00; for PIN 15 on GPIOD
    GPIOD ->MODER |= (GPIO_MODER_MODER15_0 | GPIO_MODER_MODER12_0);
    GPIOD ->OTYPER &= ~(GPIO_OTYPER_OT_15 | GPIO_OTYPER_OT_12);
    GPIOD ->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR15_0 | GPIO_OSPEEDER_OSPEEDR12_0);
    GPIOD ->PUPDR &= ~(GPIO_PUPDR_PUPDR15 | GPIO_PUPDR_PUPDR12);
    //Configue the Green LED, PD12, for STM32F407VGT6 on STM32F4 Discovery board.
    // See table 35 in section 8.3 and see section 8.4.1 in STM32F407x reference manual of RM0090
    // I/O configuration = GP output, PP: MODER=01; OTYPER=0; OSPEEDR=(01: Medium speed); PUPDR=00; for PIN 12 on GPIOD
    //GPIOD ->MODER |= GPIO_MODER_MODER12_0;
    //GPIOD ->OTYPER &= ~GPIO_OTYPER_OT_12;
    //GPIOD ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_0;
    //GPIOD ->PUPDR &= ~GPIO_PUPDR_PUPDR12;
  #elif defined(STM32L433xx)
    //configure the user LED for Output, user LED is on PB13
    // I/O configuratio = GP output, PP: MODER=01 ; OTYPER=0 ; OSPEEDR=(00 = Low); PUPDR=00 ; for PIN 13 on GPIOB for the nucleo_l433rc_p board
    BITMASK_SET(GPIOB ->MODER, GPIO_MODER_MODE13_0);
    //GPIOB ->MODER |= GPIO_MODER_MODE13_0;
    BITMASK_CLEAR(GPIOB ->OTYPER, GPIO_OTYPER_OT13);
    //GPIOB ->OTYPER &= ~(GPIO_OTYPER_OT13);
    //BITMASK_CLEAR(GPIOB ->OSPEEDR, GPIO_OSPEEDR_OSPEED13);
    BITMASK_SET(GPIOB ->OTYPER, GPIO_OSPEEDR_OSPEED13_0);
    //GPIOB ->OSPEEDR |= (GPIO_OSPEEDR_OSPEED13_0);
    BITMASK_CLEAR(GPIOB ->PUPDR, GPIO_PUPDR_PUPD13);
    //GPIOB ->PUPDR &= ~(GPIO_PUPDR_PUPD13);
  #endif

  while (1) {
    delay();

    #if defined(STM32_F100RB)
      // Read the button - the button pulls down PA0 to logic 0
      button = ((GPIOA ->IDR & 0x1) == 0);
    #elif defined(STM32_F407VG)
      //See section 8.4.5 in STM32F407x reference manual of RM0090
      // Read the button - the button pulls down PA0 to logic 0
      //(button circuit is active low)
      button = ((GPIOA ->IDR) & GPIO_IDR_IDR_0);
      //button is equal to 0 when the button is pressed!
    #elif defined(STM32L433xx)
      //Read the button - the button pulls down PC13 to logic 0
      //Read the User button on PC13 for the nucleo_l433rc_p board
      button = BITMASK_CHECK(GPIOC -> IDR, GPIO_IDR_ID13);
      //button = ((GPIOC -> IDR) & GPIO_IDR_ID13);
      //button is equal to 1 when the button is pressed
    #endif

    //break point for testing purposes
    asm("nop");

    inc();

    //this is a test this is only a test

    if (n & 1) {
      #if defined(STM32_F100RB)
        /* see 7.2.5 in stm32f100x reference manual */
        //PC8 Off
        GPIOC ->BSRR = 1 << 8 ;
      #elif defined(STM32_F407VG)
        //blue LED is a user LED connected to PD15
        //turn off light
        GPIOD ->BSRRH |= GPIO_BSRR_BS_15; //reset register
      #elif defined(STM32L433xx)
        //Turn off the user LED (PB13) on the nucleo_l433rc_p board
        //BITMASK_SET(GPIOB ->BSRR, GPIO_BSRR_BR13); //reset bit
        //break point for testing purposes
        asm("nop");
      #endif
    }
    else {
      #if defined(STM32_F100RB)
        /* see 7.2.5 in stm32f100x reference manual */
        //PC8 On
        GPIOC ->BSRR = 1 << 24;
      #elif defined(STM32_F407VG)
        //blue LED is a user LED connected to PD15
        //turn On light
        GPIOD ->BSRRL |= GPIO_BSRR_BS_15;  //set register
      #elif defined(STM32L433xx)
        //Turn ON the user LED (PB13) on the nucleo_l433rc_p board
        //BITMASK_SET(GPIOB ->BSRR, GPIO_BSRR_BS13); //set bit
        //break point for testing purposes
        asm("nop");
      #endif
    }

    //break point for testing purposes
    asm("nop");

    #if defined(STM32L433xx)
      if (button) {
    #else
      if ((n & 4) && button) {
    #endif
        #if defined(STM32_F100RB)
          /* see 7.2.5 in stm32f100x reference manual */
          //PC9 off
          GPIOC ->BSRR = 1 << 9 ;
        #elif defined(STM32_F407VG)
          // Green LED is a user LED connected to the PD12
          // turn off light
          GPIOD ->BSRRL |= GPIO_BSRR_BS_12;  //set register
        #elif defined(STM32L433xx)
          // turn off the user LED (PB13) on the nucleo_l433rc_p board
          BITMASK_SET(GPIOB ->BRR, GPIO_BRR_BR13); //reset bit
          //break point for testing purposes
          asm("nop");
        #endif
      }
      else {
        #if defined(STM32_F100RB)
          //PC9 On
          /* see 7.2.5 in stm32f100x reference manual */
          GPIOC ->BSRR = 1 << 25;
        #elif defined(STM32_F407VG)
          // Green LED is a user LED connected to the PD12
          // turn on light
          GPIOD ->BSRRH |= GPIO_BSRR_BS_12; //reset register
        #elif defined(STM32L433xx)
          // turn on the user LED (PB13) on the nucleo_l433rc_p board
          BITMASK_SET(GPIOB ->BSRR, GPIO_BSRR_BS13); //set bit
          //break point for testing purposes
          asm("nop");
        #endif
      }

    //break point for testing purposes
    asm("nop");
  } //end of While loop
}
