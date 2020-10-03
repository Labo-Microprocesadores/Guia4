/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include "SysTick.h"
#include "encoder.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t);

static char leds[] = {PIN_LED_RED, PIN_LED_BLUE,PIN_LED_GREEN};
static int current = 0;
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    gpioMode(PIN_LED_RED, OUTPUT);
    gpioMode(PIN_LED_BLUE, OUTPUT);
    gpioMode(PIN_LED_GREEN, OUTPUT);
    gpioWrite(PIN_LED_BLUE, HIGH);
    gpioWrite(PIN_LED_GREEN, HIGH);
    SysTick_Init();
    Encoder_Init();

}

/* Función que se llama constantemente en un ciclo infinito */

void App_Run (void)
{
	int moves = Encoder_GetMove();
	if (moves != 0)
	{
		gpioToggle(leds[current]);
		current += moves;
		if (current > 2){ current = 0;}
		else if(current < 0 ){current = 2;}
		gpioToggle(leds[current]);
	}
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void delayLoop(volatile uint32_t veces)
{
    while (veces--);
}

/*******************************************************************************
 ******************************************************************************/
