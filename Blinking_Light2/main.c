#if defined(STM32_F100RB)
  #include <stm32f10x.h>
  #include <stm32f10x_rcc.h>
  #include <stm32f10x_gpio.h>
#elif defined(STM32_F407VG)
  #include <stm32f4xx.h>
  #include <stm32f4xx_rcc.h>
  #include <stm32f4xx_gpio.h>
#elif defined (STM32L433xx)
  #include <STM32L433xx.h>
  //#include <stm32l4xx_ll_rcc.h>
  #include <stm32l4xx_hal.h>
  #include <stm32l4xx_nucleo.h>
  //#include <stm32l4xx_hal_cortex.h>
  #include <stm32l4xx_hal_rcc.h>
  //#include <stm32l4xx_ll_rcc.h>
  #include <stm32l4xx_hal_gpio.h>
#endif

#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK_ALL(x,y) (!(~(x) & (y)))
#define BITMASK_CHECK(x,y) (((x) & (y)) == (y))
#define BITMASK_CHECK_ANY(x,y) ((x) & (y))

//global variables
//for testing purposes
static __IO int ledval = 0;
static __IO int inc_const = 3;
static __IO uint8_t button;
static __IO int number_limit = 4000;

// Timer code gloabl variables
static __IO uint32_t TimingDelay;

static void SystemClock_80MHz(void);
static void SystemClock_24MHz(void);
static void Error_Handler(void);

void Delay(uint32_t nTime);

// increment routine
void inc(void) {
  ledval += inc_const;
  if (ledval == number_limit)
    ledval = 0;
}

/* Default 0x1FE for 0x200 alignement. Best result with 0x200 ie alignement 0x202*/
#if defined(__CC_ARM)
  #pragma arm section code = ".ROM_While1_section"
  #pragma no_inline
  void whileloop1(void)
#elif defined(__ICCARM__)
  #pragma section="ROM_While1_region"
  void whileloop1(void) @ "While1Section";
  void whileloop1(void)
#elif defined(__GNUC__)
  void __attribute__((section(".ROM_While1_section"), noinline)) whileloop1(void)
#endif
  {
    while(1);
  }
#if defined(__CC_ARM)
  #pragma arm section code
#endif

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
for the debug interface. If I’m not mistaken, they are all on port A. SWDIO is PA13, SWCLK is PA14 for both the STM32F1 and STM32F4
*/

/*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f40_41xxx.s)
       before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
*/


/* IMPORTANT Information concerning Nucleo-L433RC-P board:
    [..]
      After reset the device is running from Multiple Speed Internal oscillator
      (4 MHz) with Flash 0 wait state. Flash prefetch buffer, D-Cache
      and I-Cache are disabled, and all peripherals are off except internal
      SRAM, Flash and JTAG.

      (+) There is no prescaler on High speed (AHBs) and Low speed (APBs) busses:
          all peripherals mapped on these busses are running at MSI speed.
      (+) The clock for all peripherals is switched off, except the SRAM and FLASH.
      (+) All GPIOs are in analog mode, except the JTAG pins which
          are assigned to be used for debug purpose.

    [..]
      Once the device started from reset, the user application has to:
      (+) Configure the clock source to be used to drive the System clock
          (if the application needs higher frequency/performance)
      (+) Configure the System clock frequency and Flash settings
      (+) Configure the AHB and APB busses prescalers
      (+) Enable the clock for the peripheral(s) to be used
      (+) Configure the clock source(s) for peripherals which clocks are not
          derived from the System clock (SAIx, RTC, ADC, USB OTG FS/SDMMC1/RNG)
*/

  GPIO_InitTypeDef GPIO_InitStructure;

  #if defined(STM32L433xx)
  /*
      - Configure the Flash prefetch
      - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
      - Set NVIC Group Priority to 4
      - Low Level Initialization
  */
  HAL_Init();
 #endif

  #if defined(STM32L433xx)
  /* for the Nucleo-L433RC-P board:
      (+) Configure the clock source to be used to drive the System clock
        (if the application needs higher frequency/performance)
      (+) Configure the System clock frequency and Flash settings
      (+) Configure the AHB and APB busses prescalers
      (+) Enable the clock for the peripheral(s) to be used
  */
  //Configure the clock source to be used to drive the System clock

  // Configure the System clock frequency and Flash settings

  //Configure the AHB and SPB busses prescalers

  //Enable the clock for the peripherals I will be using


  #endif

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
  #elif defined(STM32L433xx)
    //User Button is on PC13
    //User LED is on  PB13.
    // SWDIO & SWCLK pins for the board: PA13 is SWDIO & PA14 is SWCLK (do not disable these two pins)
    // enable clocks on Port A for SWDIO/SWCLK pins; Enable Port B for LED; Enable Port C for User button
    RCC_APHB2PeriphClockCmd(RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);
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
  #elif defined(STM32L433xx)

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
  #elif defined(STM32L433xx)

  #endif

  #if defined(STM32_F100RB) || defined(STM32_F407VG)
    GPIO_Init(GPIOA , &GPIO_InitStructure);
  #elif defined(STM32L433xx)

  #endif


  #if defined(STM32_F100RB)
    // Configure SysTick Timer
    // 1 msec interrupts
    if (SysTick_Config(SystemCoreClock / 1000))
      while (1);
  #elif defined(STM32_F407VG)
    // Configure SysTick Timer
    // 168000000/1000 = 168000 ticks between interrupts
    // or 168000 ticks
    if (SysTick_Config(SystemCoreClock / 1000))
      while (1);
  #elif defined(STM32L433xx)

  #endif

  //main loop that toggles the leds and reads the USER 1 button
  while (1) {

    Delay (100); // wait 100ms

    #if defined(STM32_F100RB) || defined(STM32_F407VG)
      // Read the button - the button pulls down PA0 to logic 0
      button = (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0);
    #elif defined(STM32L433xx)

    #endif

    inc();

    // toggle leds based on the value of ledval

    #if defined(STM32_F100RB) || defined(STM32_F407VG)
      if (ledval & 1) {
        #if defined(STM32_F100RB)
          //LED on PC8
          //turn off light
          GPIO_WriteBit(GPIOC , GPIO_Pin_8 , Bit_RESET);
        #elif defined(STM32_F407VG)
          //blue LED is a user LED connected to PD15
          //turn off light
          GPIO_WriteBit(GPIOD , GPIO_Pin_15 , Bit_RESET);
        #endif
      }
      else {
        #if defined(STM32_F100RB)
          //LED on PC8
          //turn on light
          GPIO_WriteBit(GPIOC , GPIO_Pin_8 , Bit_SET);
        #elif defined(STM32_F407VG)
          //blue LED is a user LED connected to PD15
          //turn on light
          GPIO_WriteBit(GPIOD , GPIO_Pin_15 , Bit_SET);
        #endif
      }
    #elif defined(STM32L433xx)
      //break point for testing purposes
      asm("nop");
    #endif

    #if defined(STM32_F100RB) || defined(STM32_F407VG)
      if ((ledval & 4) && button) {
    #elif defined(STM32L433xx)
      if (button) {
    #endif
        // button is equal to 1 if the button is NOT pressed
        #if defined(STM32_F100RB)
          // LED on PC9 and USER button on PA0; (button circuit is active low)
          // turn off light
          GPIO_WriteBit(GPIOC , GPIO_Pin_9 , Bit_SET);
        #elif defined(STM32_F407VG)
          // Green LED is a user LED connected to the PD12
          // turn off light
          GPIO_WriteBit(GPIOD , GPIO_Pin_12 , Bit_SET);
        #elif defined(STM32L433xx)

        #endif
      }
      else {
        //button is equal to 0 when the button is pressed
        #if defined(STM32_F100RB)
          // LED on PC9 and USER button on PA0; (button circuit is active low)
          //turn on light
          GPIO_WriteBit(GPIOC , GPIO_Pin_9 , Bit_RESET);
        #elif defined(STM32_F407VG)
          // Green LED is a user LED connected to the PD12
          // turn on light
          GPIO_WriteBit(GPIOD , GPIO_Pin_12 , Bit_RESET);
        #elif defined(STM32L433xx)

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