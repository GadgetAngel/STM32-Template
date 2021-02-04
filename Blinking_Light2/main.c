#include "stm32f10x.h"
#include "..\..\STM32-Template\.pio\libdeps\disco_f100rb\STM32F10x_StdPeriph_Lib_V3.5.0_mod\Libraries\STM32F10x_StdPeriph_Driver\stm32f10x_rcc.h"
#include "..\..\STM32-Template\.pio\libdeps\disco_f100rb\STM32F10x_StdPeriph_Lib_V3.5.0_mod\Libraries\STM32F10x_StdPeriph_Driver\stm32f10x_gpio.h"

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

  GPIO_InitTypeDef GPIOC_InitStructure;
  //GPIO_InitTypeDef GPIOA_InitStructure;


  // Enable Peripheral Clocks
  //enable clocks for Port C for the LEDs on PC8 and PC9
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
  //enable clocks for Port A for the USER button on PA0
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);


  // Configure Pins
  GPIO_StructInit (&GPIOC_InitStructure);
  // configure PC9 pin
  GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_9;
  // configure PC8 pin
  //GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC , &GPIOC_InitStructure);
  // configure PA0 pin
  //GPIO_StructInit (&GPIOA_InitStructure);
  //GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_0;
  //GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  //GPIO_Init(GPIOA , &GPIOA_InitStructure);


  // Configure SysTick Timer
  if (SysTick_Config(SystemCoreClock / 1000))
    while (1);

  //main loop that toggles the leds and reads the USER 1 button
  while (1) {

    Delay (250); // wait 250ms

    // Read the button - the button pulls down PA0 to logic 0
    //button = (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0);

    inc();

    // toggle leds based on the value of ledval

    //LED on PC8
    //if (ledval & 1) {
      //turn off light
      //GPIO_WriteBit(GPIOC , GPIO_Pin_8 , Bit_RESET);
    //}
   // else {
      //turn on light
      //GPIO_WriteBit(GPIOC , GPIO_Pin_8 , Bit_SET);
    //}

    // LED on PC9 and USER button on PA0
    //if ((ledval & 4) && button) {
    if ((ledval & 4)) {
      // turn off light
      GPIO_WriteBit(GPIOC , GPIO_Pin_9 , Bit_RESET);
    }
    else {
      //turn on light
      GPIO_WriteBit(GPIOC , GPIO_Pin_9 , Bit_SET);
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