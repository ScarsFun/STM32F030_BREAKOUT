/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic // define objects in main module
#include "osObjects.h" // RTOS object definitions
#include "stm32f0xx.h"
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>

/*----------------------------------------------------------------------------
 * blinkLED: blink LED 
 *----------------------------------------------------------------------------*/
void blinkLED(void const* argument)
{
    for (;;) {
        GPIOA->ODR ^= (1 << 4);
        osDelay(500);
    }
}


osThreadId tid_blinkLED;
osThreadDef(blinkLED, osPriorityNormal, 1, 0);

/*----------------------------------------------------------------------------
 * Configure GPIO LED
 *----------------------------------------------------------------------------*/
void LED_Config(void)
{
    GPIO_InitTypeDef Gp; //Create GPIO struct
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    Gp.GPIO_Pin = GPIO_Pin_4; //Set pins inside the struct
    Gp.GPIO_Mode = GPIO_Mode_OUT; //Set GPIO pins as output
    Gp.GPIO_OType = GPIO_OType_PP; //Ensure output is push-pull vs open drain
    Gp.GPIO_PuPd = GPIO_PuPd_NOPULL; //No internal pullup resistors required
    Gp.GPIO_Speed = GPIO_Speed_Level_1; //Set GPIO speed to lowest
    GPIO_Init(GPIOA, &Gp); //Assign struct to GPIOA
}



int main(void)
{
    osKernelInitialize(); // initialize CMSIS-RTOS
    // initialize peripherals here
    LED_Config(); // LED Initialization
    // create 'thread' functions that start executing,
    tid_blinkLED = osThreadCreate(osThread(blinkLED), NULL);
    osKernelStart(); // start thread execution
}
