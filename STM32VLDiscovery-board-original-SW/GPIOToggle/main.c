/**
  ******************************************************************************
  * @file    Examples/GPIOToggle/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    09/13/2010
  * @brief   Main program body.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "STM32vldiscovery.h"

GPIO_InitTypeDef GPIO_InitStructure;
static __IO int counter32 = 0;

// Timer code gloabl variables
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime);

int main(void) {

  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */

  /* Configure all unused GPIO port pins in Analog Input mode (floating input
     trigger OFF), this will reduce the power consumption and increase the device
     immunity against EMI/EMC *************************************************/

  // this is an example code from the ST library, the problem here is that if
  // you disable GPIOA you will also be disabling the SWDIO and SWCLK lines that
  // are needed to upload new firmware to the device.  I say only enable the pins
  // you will be using to run the program.
  RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC), ENABLE);

  // Configure SysTick Timer
  if (SysTick_Config(SystemCoreClock / 1000))
     while (1);

  /* Initialize Leds LD3 and LD4 mounted on STM32VLDISCOVERY board */
  STM32vldiscovery_LEDInit(LED3);  //PC9
  STM32vldiscovery_LEDInit(LED4);  //PC8

  while (1) {
    /* Turn on LD2 and LD3 */
    STM32vldiscovery_LEDOn(LED3);
    STM32vldiscovery_LEDOff(LED4);
   /* Insert delay */
    //Delay(0xAFFFF);
    Delay(100);
    /* Turn off LD3 and LD4 */
    STM32vldiscovery_LEDOff(LED3);
    STM32vldiscovery_LEDOn(LED4);
    /* Insert delay */
    //Delay(0xAFFFF);
    Delay(100);

    counter32++;
  }
}

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
