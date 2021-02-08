#if defined(STM32_F100RB)
  #include <stm32f10x.h>
  #include <stm32f10x_rcc.h>
  #include <stm32f10x_gpio.h>
#elif defined(STM32_F407VG)
  #include <stm32f4xx.h>
  #include <stm32f4xx_rcc.h>
  #include <stm32f4xx_gpio.h>
#endif

//global variables
//for testing purposes
int ledval = 0;
int inc_const = 3;
int button;
int number_limit = 4000;

// Timer code gloabl variables
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime);

// increment routine
void inc(void) {
  ledval += inc_const;
  if (ledval == number_limit)
    ledval = 0;
}

int main(void) {

  GPIO_InitTypeDef GPIO_InitStructure;

  #if defined(STM32_F100RB)
    // Enable Peripheral Clocks
    //enable clocks for Port C for the LEDs on PC8 and PC9, and Port A for the User button on PA0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA , ENABLE);
  #elif defined(STM32_F407VG)
    //Enable clocks for GPIOD for Pin 15 & Pin 12 for the blue LED & Green LED; and GPIOA Pin 0 for User button
    //blue LED is a user LED connected to PD15 of the STM32F407VGT6 on STM32F4 Discovery board.
    //Green LED is a user LED connected to the PD12 of the STM32F407VGT6 on STM32F4 Discovery board.
    //user button is on PA0 PIN of the STM32F407VG on STM32F4 Discovery board.
    // See 6.3.10 in STM32F407x reference manual of RM0090
    // Enable the GPIOA (bit 0) and GPIOD (bit 3)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA , ENABLE);
  #endif

  // Configure Pins
  GPIO_StructInit (&GPIO_InitStructure);

  #if defined(STM32_F100RB)
    // configure PC9 pin and PC8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    // correct use of the GPI_Init call (comment out this out when you want to cause an assertion violation):
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    // un-comment the below statement  when you want to cause an assertion violation and use GDB to find it (part of Exercise 4.1)
    //GPIO_Init((void *) 66U, &GPIO_InitStructure);
  #elif defined(STM32_F407VG)
    //blue LED is a user LED connected to PD15 of the STM32F407VGT6 on STM32F4 Discovery board.
    //Green LED is a user LED connected to the PD12 of the STM32F407VGT6 on STM32F4 Discovery board.
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    // correct use of the GPI_Init call (comment out this out when you want to cause an assertion violation):
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    // un-comment the below statement  when you want to cause an assertion violation and use GDB to find it (part of Exercise 4.1)
    //GPIO_Init((void *) 66U, &GPIO_InitStructure);
  #endif

  #if defined(STM32_F100RB)
    // configure PA0 pin
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  #elif defined(STM32_F407VG)
    // configure PA0 pin; Input with Pull Down
    //Configure the user Button on PA0 for STM32F407VGT6 on STM32F4 Discovery board.
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  #endif

  #if defined(STM32_F100RB) || defined(STM32_F407VG)
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    // Configure SysTick Timer
    if (SysTick_Config(SystemCoreClock / 1000))
      while (1);
  #endif

  //main loop that toggles the leds and reads the USER 1 button
  while (1) {

    Delay (250); // wait 250ms

    #if defined(STM32_F100RB) || defined(STM32_F407VG)
      // Read the button - the button pulls down PA0 to logic 0
      button = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0);
    #endif

    inc();

    // toggle leds based on the value of ledval


    if (ledval & 1) {
      #if defined(STM32_F100RB)
        //LED on PC9
        //turn off light
        GPIO_WriteBit(GPIOC , GPIO_Pin_9 , Bit_RESET);
      #elif defined(STM32_F407VG)
        // Green LED is a user LED connected to the PD12
        // turn off light
        GPIO_WriteBit(GPIOD , GPIO_Pin_12 , Bit_RESET);
      #endif
    }
    else {
      #if defined(STM32_F100RB)
        //LED on PC9
        //turn on light
        GPIO_WriteBit(GPIOC , GPIO_Pin_9 , Bit_SET);
      #elif defined(STM32_F407VG)
        // Green LED is a user LED connected to the PD12
        // turn on light
        GPIO_WriteBit(GPIOD , GPIO_Pin_12 , Bit_SET);
      #endif
    }


    if ((ledval & 4) && button) {
      #if defined(STM32_F100RB)
        // LED on PC8 and USER button on PA0; (button circuit is active low)
        //if ((ledval & 4)) {
        // turn off light
        GPIO_WriteBit(GPIOC , GPIO_Pin_8 , Bit_SET);
      #elif defined(STM32_F407VG)
        //blue LED is a user LED connected to PD15
        //turn off light
        GPIO_WriteBit(GPIOD , GPIO_Pin_15 , Bit_SET);
      #endif
    }
    else {
      #if defined(STM32_F100RB)
        // LED on PC8
        //turn on light
        GPIO_WriteBit(GPIOC , GPIO_Pin_8 , Bit_RESET);
      #elif defined(STM32_F407VG)
        //blue LED is a user LED connected to PD15
        //turn on light
        GPIO_WriteBit(GPIOD , GPIO_Pin_15 , Bit_RESET);
      #endif
    }

  } //end of while loop
} //end of main

// Timer code routines
void Delay(uint32_t nTime) {
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void SysTick_Handler(void) {
  if (TimingDelay != 0x00)
    TimingDelay --;
}

#ifdef USE_FULL_ASSERT

  void assert_failed(uint8_t* file , uint32_t line) {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
  }

#endif