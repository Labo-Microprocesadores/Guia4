/*
 * encoder.c
 *
 *  Created on: 25 sep. 2020
 *      Author: Grupo 2
 */

#include "encoder.h"
#include "SysTick.h"
#include "gpio.h"
#include "board.h"
#include <stdbool.h>

/****** Variable del Driver ***********/
static bool existingEvent = false;
static bool statusA = false;
static bool statusB = false;
static int moves = 0;
/*************************************/

/******** Funciones internas *************/
void lookForMoves(void);
/************************************/

void Encoder_Init(void)
{
	static bool init=false;
	if(init==false)
	{
		init = true;
		gpioMode(ENCODER_A,INPUT);
		gpioMode(ENCODER_B,INPUT);
		SysTick_AddCallback(&lookForMoves, SYSTICK_ISR_PERIOD_S);
		statusA = gpioRead(ENCODER_A);
		statusB = gpioRead(ENCODER_B);
	}
}

int Encoder_GetMove(void)
{
	if(existingEvent)
	{
		int ret = moves;
		moves = 0;
		existingEvent = false;
		return ret;
	}
	return 0;
}

void lookForMoves(void)
{
	if(!existingEvent)
	{
		bool auxA = gpioRead(ENCODER_A);
		bool auxB = gpioRead(ENCODER_B);
		if (statusA == auxA && statusB == auxB)
		{
			return;
		}
		else if(statusA != auxA)
		{
			if(moves != 0)
			{
				existingEvent = auxA && auxB;
			}
			else
			{
				moves--;
			}
		}
		else
		{
			if(moves != 0)
			{
				existingEvent = auxA && auxB;
			}
			else
			{
				moves++;
			}
		}
		statusA = auxA;
		statusB = auxB;
	}
}
